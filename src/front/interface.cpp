#include "interface.hpp"
#include "accont.hpp"
#include "bank_status.hpp"
#include "base_payload.hpp"
#include "formater.hpp"
#include "money.hpp"
#include "sysbank.hpp"
#include <exception>
#include <string>

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

    Status result = cb->openAccont(bank_id, accont_id);
    switch (result) {
        case SUCCESS:
            return FinalPayLoad({op, SUCCESS, accont_id});
        case ALREADY_EXIST:
            return FinalPayLoad({op, ALREADY_EXIST, accont_id});
        case BANK_NOT_FOUND:
            return FinalPayLoad({op, BANK_NOT_FOUND, bank_id});
        default:
            throw std::exception();
    };
}

FinalPayLoad cmd::bank_info(CentralBank* cb, std::string bank_id) {
    Operation op = INFO_BANK;

    Bank* b = cb->getBank(bank_id);
    if (b == nullptr) {
        return FinalPayLoad({op, NOT_FOUND, bank_id});
    }
    return FinalPayLoad({op, SUCCESS, payload::Bank{b->getID(), b->getAccontN()}});
}


FinalPayLoad cmd::account_info(CentralBank* cb, std::string bank_id, std::string accont_id) {
    Operation op = INFO_ACCOUNT;

    Bank* b = cb->getBank(bank_id);
    if (b == nullptr) {
        return FinalPayLoad({op, BANK_NOT_FOUND, bank_id});
    }

    const Account* a = b->getAccont(accont_id);
    if (a == nullptr) {
        return FinalPayLoad({op, ACCOUNT_NOT_FOUND, accont_id});
    }

    return FinalPayLoad({op, SUCCESS,
        payload::Account{accont_id, a->formatBalance()}
    });
}


FinalPayLoad cmd::money_new(CentralBank* cb, std::string bank_id, std::string money_id, std::string money_symbol) {
    Operation op = NEW_MONEY;

    Status result = cb->newMoney(bank_id, money_id, money_symbol);

    switch (result) {
        case SUCCESS:
            return FinalPayLoad({op, SUCCESS, MoneyType{money_id, money_symbol}});
        case BANK_NOT_FOUND:
            return FinalPayLoad({op, BANK_NOT_FOUND, bank_id});
        case ALREADY_EXIST:
            return FinalPayLoad({op, ALREADY_EXIST, money_id});
        default:
            throw std::exception();
    }
}

FinalPayLoad cmd::money_info(CentralBank* cb, std::string bank_id, std::string money_id) {
    Operation op = INFO_MONEY;

    Bank* b = cb->getBank(bank_id);
    if (b == nullptr) {
        return FinalPayLoad({op, BANK_NOT_FOUND, bank_id});
    }
    MoneyType* mt = b->getMoney(money_id);
    if(mt == nullptr) {
        return FinalPayLoad({op, MONEY_NOT_FOUND, money_id});
    }
    return FinalPayLoad({op, SUCCESS, *mt});
}


FinalPayLoad cmd::deposit(CentralBank* cb, std::string bank_id, std::string user_id, std::string money_id, cents value) {
    Operation op = DEPOSIT;
    Status result = cb->deposit(bank_id, value, money_id, user_id);
    MoneyType* money_t;

    switch (result) {
        case BANK_NOT_FOUND:
            return FinalPayLoad({op, BANK_NOT_FOUND, bank_id});
        case ACCOUNT_NOT_FOUND:
            return FinalPayLoad({op, ACCOUNT_NOT_FOUND, user_id});
        case MONEY_NOT_FOUND:
            return FinalPayLoad({op, MONEY_NOT_FOUND, money_id});
        case SUCCESS:
            money_t = cb->getBank(bank_id)->getMoney(money_id);
            return FinalPayLoad({op, SUCCESS, payload::Deposit{value, *money_t, user_id}});
        default:
            throw std::exception();
    }
}


FinalPayLoad cmd::pay(CentralBank* cb, std::string bank_id, cents value, std::string money_id, std::string from_id) {
    Operation op = PAYMENT;
    Status result = cb->pay(bank_id, value, money_id, from_id);

    MoneyType* money_t;

    switch (result) {
        case BANK_NOT_FOUND:
            return FinalPayLoad({op, BANK_NOT_FOUND, bank_id});
        case ACCOUNT_NOT_FOUND:
            return FinalPayLoad({op, ACCOUNT_NOT_FOUND, from_id});
        case MONEY_NOT_FOUND:
            return FinalPayLoad({op, MONEY_NOT_FOUND, money_id});
        case NOT_ENOUGH_BALANCE:
            return FinalPayLoad({op, NOT_ENOUGH_BALANCE, std::to_string(value)});
        case SUCCESS:
            money_t = cb->getBank(bank_id)->getMoney(money_id);
            return FinalPayLoad({op, SUCCESS, payload::Pay{value, *money_t, from_id}});
        default:
            throw std::exception();
    }
}
FinalPayLoad cmd::transference(CentralBank* cb, std::string bank_id, cents value, std::string money_id, std::string from_id, std::string to_id) {
    Operation op = TRANSFERENCE;
    Status result = cb->transference(bank_id, value, money_id, from_id, to_id);
    MoneyType* money_t;

    switch (result) {
        case BANK_NOT_FOUND:
            return FinalPayLoad({op, BANK_NOT_FOUND, bank_id});
        case PAYER_NOT_FOUND:
            return FinalPayLoad({op, PAYER_NOT_FOUND, from_id});
        case RECIEVER_NOT_FOUND:
            return FinalPayLoad({op, RECIEVER_NOT_FOUND, to_id});
        case MONEY_NOT_FOUND:
            return FinalPayLoad({op, MONEY_NOT_FOUND, money_id});
        case NOT_ENOUGH_BALANCE:
            return FinalPayLoad({op, NOT_ENOUGH_BALANCE, std::to_string(value)});
        case SUCCESS:
            money_t = cb->getBank(bank_id)->getMoney(money_id);
            return FinalPayLoad({op, SUCCESS, payload::Trasference{value, *money_t, from_id, to_id}});
        default:
            throw std::exception();
    }
}
