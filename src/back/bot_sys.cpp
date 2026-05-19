#include "bot_sys.hpp"
#include "accont.hpp"
#include "bank_status.hpp"
#include "base_payload.hpp"



BasePayLoad DiogoBotSys::open_bank(std::string bank_id) {
    Operation op = OPEN_BANK;
    Status result = central_bank.openBank(bank_id);
    const Bank* b = central_bank.getBank(bank_id);
    if (result == SUCCESS) {
        return {op, SUCCESS, payload::Bank{b->getID(), b->getAccontN()}};
    } else {
        return {op, ALREADY_EXIST, bank_id};
    }
}


BasePayLoad DiogoBotSys::open_accont(std::string bank_id, std::string accont_id) {
    Operation op = OPEN_ACCONT;

    Bank* b = central_bank.getBank(bank_id);
    if (b == nullptr) {return {op, BANK_NOT_FOUND, bank_id};}

    Status result = b->openAccont(accont_id);

    if (result == SUCCESS) {
        return {op, SUCCESS, accont_id};

    } else if(result == ALREADY_EXIST) {
        return {op, ALREADY_EXIST, accont_id};

    } else throw std::exception();
}

BasePayLoad DiogoBotSys::bank_info(std::string bank_id) {
    Operation op = INFO_BANK;

    Bank* b = central_bank.getBank(bank_id);
    if (b == nullptr) {
        return {op, NOT_FOUND, bank_id};
    }
    return {op, SUCCESS, payload::Bank{b->getID(), b->getAccontN()}};
}


BasePayLoad DiogoBotSys::account_info(std::string bank_id, std::string accont_id) {
    Operation op = INFO_ACCOUNT;

    Bank* b = central_bank.getBank(bank_id);
    if (b == nullptr) {
        return {op, BANK_NOT_FOUND, bank_id};
    }

    const Account* a = b->getAccont(accont_id);
    if (a == nullptr) {
        return {op, ACCOUNT_NOT_FOUND, accont_id};
    }

    return {op, SUCCESS,
        payload::Account{accont_id, a->formatBalance()}
    };
}


BasePayLoad DiogoBotSys::money_new(std::string bank_id, std::string money_id, std::string money_symbol) {
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
