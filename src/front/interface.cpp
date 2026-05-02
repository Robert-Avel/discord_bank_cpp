#include "interface.hpp"
#include "accont.hpp"
#include "bank_status.hpp"
#include "base_payload.hpp"
#include "formater.hpp"
#include "money.hpp"
#include "sysbank.hpp"
#include <sstream>

//Interface de Comandos

FinalPayLoad cmd::open_bank(CentralBank* cb,std::string bank_id) {
    Operation op = OPEN_BANK;

    Status result = cb->openBank(bank_id);
    const Bank* b = cb->getBank(bank_id);
    if (result == SUCCESS) {
        return FinalPayLoad({op, SUCCESS, payload::Bank{b->getID(), b->getAccontN()}});
    } else {
        return FinalPayLoad({op, ALREADY_EXIST, bank_id});
    }
}


FinalPayLoad cmd::open_accont(CentralBank* cb, std::string bank_id, std::string accont_id) {
    Operation op = OPEN_ACCONT;

    Bank* b = cb->getBank(bank_id);
    if (b == nullptr) {
        return FinalPayLoad({op, NOT_FOUND, bank_id});
    }
    Status result = b->openAccont(accont_id);
    if (result == SUCCESS) {
        return FinalPayLoad({op, SUCCESS, accont_id});
    } else {
        return FinalPayLoad({op, ALREADY_EXIST, accont_id});
    }
}

FinalPayLoad cmd::bank_info(CentralBank* cb, std::string bank_id) {
    Operation op = INFO_BANK;

    Bank* b = cb->getBank(bank_id);
    if (b == nullptr) {
        return FinalPayLoad({op, NOT_FOUND, bank_id});
    }
    return FinalPayLoad({op, NOT_FOUND, payload::Bank{b->getID(), b->getAccontN()}});
}


FinalPayLoad cmd::account_info(CentralBank* cb, std::string bank_id, std::string accont_id) {
    Operation op = INFO_ACCOUNT;
    std::stringstream buffer;

    Bank* b = cb->getBank(bank_id);
    if (b == nullptr) {
        buffer << "Bank: " << bank_id;
        return FinalPayLoad({op, NOT_FOUND, buffer.str()});
    }

    const Account* a = b->getAccont(accont_id);
    if (a == nullptr) {
        buffer << "Account: " << accont_id;
        return FinalPayLoad({op, NOT_FOUND, buffer.str()});
    }

    return FinalPayLoad({INFO_ACCOUNT, SUCCESS,
        payload::Account{accont_id, a->formatBalance()}
    });
}


FinalPayLoad cmd::money_new(CentralBank* cb, std::string bank_id, std::string money_id, std::string money_symbol) {
    Operation op = NEW_MONEY;
    std::stringstream buffer;

    Bank* b = cb->getBank(bank_id);
    if (b == nullptr) {
        buffer << "Bank: " << bank_id;
        return FinalPayLoad({op, NOT_FOUND, buffer.str()});
    }
    Status s = b->moneyNew(money_id, money_symbol);
    if(s == ALREADY_EXIST) {
        buffer << "Money: " << money_id;
        return FinalPayLoad({op, ALREADY_EXIST, buffer.str()});
    }
    return FinalPayLoad({op, SUCCESS, MoneyType{money_id, money_symbol}});
}

FinalPayLoad cmd::money_info(CentralBank* cb, std::string bank_id, std::string money_id) {
    Operation op = INFO_MONEY;
    std::stringstream buffer;

    Bank* b = cb->getBank(bank_id);
    if (b == nullptr) {
        buffer << "Bank: " << bank_id;
        return FinalPayLoad({op, NOT_FOUND, buffer.str()});
    }
    MoneyType* mt = b->moneyGet(money_id);
    if(mt == nullptr) {
        buffer << "Money: " << money_id;
        return FinalPayLoad({op, NOT_FOUND, buffer.str()});
    }
    return FinalPayLoad({op, SUCCESS, *mt});
}


FinalPayLoad cmd::deposit(CentralBank* cb, std::string bank_id, std::string user_id, std::string money_id, cents value) {
    Operation op = DEPOSIT;
    std::stringstream buffer;

    Bank* b = cb->getBank(bank_id);
    if (b == nullptr) {
        buffer << "Bank: " << bank_id;
        return FinalPayLoad({op, NOT_FOUND, buffer.str()});
    }
    MoneyType* mt = b->moneyGet(money_id);
    if(mt == nullptr) {
        buffer << "Money: " << money_id;
        return FinalPayLoad({op, NOT_FOUND, buffer.str()});
    }
    const Account* a = b->getAccont(user_id);
    if (a == nullptr) {
        buffer << "Account: " << user_id;
        return FinalPayLoad({op, NOT_FOUND, buffer.str()});
    }

    b->deposit(value, mt->id, mt->symbol, user_id);
    return FinalPayLoad({
        op, SUCCESS, payload::Deposit{value, *mt, user_id}
    });
}
