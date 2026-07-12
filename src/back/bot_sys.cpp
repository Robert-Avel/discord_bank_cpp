#include "bot_sys.hpp"
#include "accont.hpp"
#include "bank.hpp"
#include "status.hpp"
#include "base_payload.hpp"
#include "client_user.hpp"
#include "money.hpp"
#include "saver.hpp"
#include <ctime>
#include <fstream>
#include <ios>
#include <mutex>
#include <string>


void DiogoBotSys::linkAccounts() {
    for(Bank& b: central_bank.getBankData()) {
        for(ClientUser& cu: b.getClientData().getAllClient()) {
            Account* a = b.getAccont(cu.getUserID());
            if(a != nullptr) {
                cu.linkAccount(*a);
            }
        }
    }
}


BasePayLoad DiogoBotSys::open_bank(std::string bank_id) {
    std::lock_guard<std::mutex> lock(mutex);

    Operation op = OPEN_BANK;
    Status result = central_bank.openBank(bank_id);
    const Bank* b = central_bank.getBank(bank_id);
    if (result == SUCCESS) {
        return {op, SUCCESS, payload::Bank{b->getID(), b->getAccontN()}};
    } else {
        return {op, ALREADY_EXIST, bank_id};
    }
}


BasePayLoad DiogoBotSys::init_user(std::string bank_id, std::string user_id, std::string user_name) {
    std::lock_guard<std::mutex> lock(mutex);


    Operation op = INIT_USER;

    Bank* b = central_bank.getBank(bank_id);
    if (b == nullptr) {return {op, BANK_NOT_FOUND, bank_id};}

    return {
        op,
        b->newClient(user_id, user_name),
        user_id
    };
}

BasePayLoad DiogoBotSys::bank_info(std::string bank_id) {
    std::lock_guard<std::mutex> lock(mutex);


    Operation op = INFO_BANK;

    Bank* b = central_bank.getBank(bank_id);
    if (b == nullptr) {
        return {op, BANK_NOT_FOUND, bank_id};
    }
    return {op, SUCCESS, payload::Bank{b->getID(), b->getAccontN()}};
}


BasePayLoad DiogoBotSys::user_info(std::string bank_id, std::string user_id) {
    std::lock_guard<std::mutex> lock(mutex);


    Operation op = INFO_ACCOUNT;

    Bank* b = central_bank.getBank(bank_id);
    if (b == nullptr) {
        return {op, BANK_NOT_FOUND, bank_id};
    }

    ClientUser* c = b->getClient(user_id);
    if (c == nullptr) {return {op, CLIENT_NOT_FOUND, user_id};};


    if (c->getAccount() == nullptr) {
        return {op, ACCOUNT_NOT_FOUND, user_id};
    }


    std::string job_info = (c->getJob() ? c->getJob()->getJobName(): "N/A");


    return {op, SUCCESS,
        payload::Client{c->getGlobalName(), user_id, bank_id, c->getAccount()->formatBalance(), job_info}
    };
}


BasePayLoad DiogoBotSys::money_new(std::string bank_id, std::string money_id, std::string money_symbol) {
    std::lock_guard<std::mutex> lock(mutex);


    Operation op = NEW_MONEY;

    Bank* b = central_bank.getBank(bank_id);
    if (b == nullptr) {return {op, BANK_NOT_FOUND, bank_id};}

    Status result = b->moneyNew(money_id, money_symbol);

    if (result == SUCCESS) {
        return {op, SUCCESS, MoneyType{money_id, money_symbol}};

    } else if(result == ALREADY_EXIST) {
        return {op, ALREADY_EXIST, money_id};

    } else throw std::exception();
}

BasePayLoad DiogoBotSys::money_info(std::string bank_id, std::string money_id) {
    std::lock_guard<std::mutex> lock(mutex);


    Operation op = INFO_MONEY;

    Bank* b = central_bank.getBank(bank_id);
    if (b == nullptr) {
        return {op, BANK_NOT_FOUND, bank_id};
    }
    MoneyType* mt = b->getMoney(money_id);
    if(mt == nullptr) {
        return {op, MONEY_NOT_FOUND, money_id};
    }
    return {op, SUCCESS, *mt};
}


BasePayLoad DiogoBotSys::deposit(std::string bank_id, std::string to_id, std::string money_id, cents value) {
    std::lock_guard<std::mutex> lock(mutex);


    Operation op = DEPOSIT;

    Bank* b = central_bank.getBank(bank_id);
    if(b == nullptr) {
        return {op, BANK_NOT_FOUND, bank_id};
    }

    Account* to = b->getAccont(to_id);
    if(to == nullptr) {
        return {op, PAYER_NOT_FOUND, to_id};
    }

    MoneyType* money = b->getMoney(money_id);
    if(money == nullptr) {
        return {op, MONEY_NOT_FOUND, money_id};
    }

    Status result = b->depositWhiteList(to, value, money->id);

    if(result == SUCCESS) {
        return {op, SUCCESS, payload::Deposit{value, *money, to_id}};
    } else {
        return {op, FAILURE, "Critical"};
    }
}


BasePayLoad DiogoBotSys::pay(std::string bank_id, cents value, std::string money_id, std::string from_id) {
    std::lock_guard<std::mutex> lock(mutex);


    Operation op = PAYMENT;

    Bank* b = central_bank.getBank(bank_id);
    if(b == nullptr) {
        return {op, BANK_NOT_FOUND, bank_id};
    }
    Account* from = b->getAccont(from_id);
    if(from == nullptr) {
        return {op, PAYER_NOT_FOUND, from_id};
    }

    MoneyType* money = b->getMoney(money_id);
    if(money == nullptr) {
        return {op, MONEY_NOT_FOUND, money_id};
    }

    Status result = b->pay(from, value, money->id);
    if(result == NOT_ENOUGH_BALANCE) {
        return {op, NOT_ENOUGH_BALANCE, std::to_string(value)};
    } else if(result == SUCCESS) {
        return {op, SUCCESS, payload::Pay{value, *money, from_id}};
    } else {
        return {op, FAILURE, "Critical"};
    }
}

BasePayLoad DiogoBotSys::transference(std::string bank_id, cents value, std::string money_id, std::string from_id, std::string to_id) {
    std::lock_guard<std::mutex> lock(mutex);


    Operation op = TRANSFERENCE;

    Bank* b = central_bank.getBank(bank_id);
    if(b == nullptr) {
        return {op, BANK_NOT_FOUND, bank_id};
    }
    Account* from = b->getAccont(from_id);
    if(from == nullptr) {
        return {op, PAYER_NOT_FOUND, from_id};
    }

    Account* to= b->getAccont(to_id);
    if(to == nullptr) {
        return {op, RECIEVER_NOT_FOUND, to_id};
    }

    MoneyType* money = b->getMoney(money_id);
    if(money == nullptr) {
        return {op, MONEY_NOT_FOUND, money_id};
    }

    Status result = b->transference(from, to, value, money->id, money->symbol);
    if(result == NOT_ENOUGH_BALANCE) {
        return {op, NOT_ENOUGH_BALANCE, std::to_string(value)};
    } else if(result == SUCCESS) {
        return {op, SUCCESS, payload::Trasference{value, *money, from_id, to_id}};
    } else {
        return {op, FAILURE, "Critical"};
    }
}


BasePayLoad DiogoBotSys::hire_user(std::string bank_id, std::string client_id, std::string role_name, std::string money_id, cents salary) {
    std::lock_guard<std::mutex> lock(mutex);


    Operation op = HIRE_USER;

    Bank* b = this->central_bank.getBank(bank_id);
    if(b == nullptr) {return {op, BANK_NOT_FOUND, bank_id};}


    ClientUser* cu = b->getClient(client_id);
    if(cu == nullptr) {return {op, CLIENT_NOT_FOUND, client_id};}

    MoneyType* m = b->getMoney(money_id);
    if(m == nullptr) {return {op, MONEY_NOT_FOUND, money_id};}

    Money f_salary{*m, salary};

    return {
        op,
        cu->autoHire(role_name, f_salary),
        payload::ImprovisedHire{role_name, f_salary}
    };
}


BasePayLoad DiogoBotSys::fire_user(std::string bank_id, std::string client_id) {
    std::lock_guard<std::mutex> lock(mutex);


    Operation op = FIRE_USER;

    Bank* b = this->central_bank.getBank(bank_id);
    if(b == nullptr) {return {op, BANK_NOT_FOUND, bank_id};}


    ClientUser* cu = b->getClient(client_id);
    if(cu == nullptr) {return {op, CLIENT_NOT_FOUND, client_id};}

    const ImprovisedJob* job = cu->getJob();
    if(job == nullptr) {return {op, NO_JOB, client_id};}


    return {
        op,
        cu->autoFire(),
        payload::ImprovisedHire{job->getJobName(), job->getSalary()}
    };
}


BasePayLoad DiogoBotSys::pay_client(std::string bank_id, std::string client_id) {
    std::lock_guard<std::mutex> lock(mutex);


    Operation op = PAY_CLIENT;

    Bank* b = this->central_bank.getBank(bank_id);
    if(b == nullptr) {return {op, BANK_NOT_FOUND, bank_id};}


    ClientUser* cu = b->getClient(client_id);
    if(cu == nullptr) {return {op, CLIENT_NOT_FOUND, client_id};}

    const ImprovisedJob* job = cu->getJob();
    if(job == nullptr) {return {op, NO_JOB, client_id};}


    if(!cu->canBPayed()) {
        time_t next_pay = cu->getLastPay() + DAY_T;
        return {
            op,
            IN_COOLDOWN,
            std::string(std::ctime(&next_pay))
        };
    }

    return {
        op,
        cu->salaryPay(),
        payload::Deposit{job->getSalary().value, job->getSalary()._mt, client_id}
    };
}


bool DiogoBotSys::save(std::string filename) {
    std::ofstream saver(filename, std::ios::binary | std::ios::trunc | std::ios::in);
    if(!saver) {
        return false;
    }
    save::central_bank(this->central_bank, saver);
    return true;
}
