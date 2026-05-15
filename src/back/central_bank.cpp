#include "central_bank.hpp"
#include "accont.hpp"
#include "bank.hpp"
#include "bank_status.hpp"
#include "money.hpp"
#include "saver.hpp"


Bank* CentralBank::getBank(std::string id) {
    for(Bank& b: banks) {
        if(b.getID() == id) {
            return &b;
        }
    }
    return nullptr;
}

Status CentralBank::openBank(std::string id) {
    if(getBank(id) == nullptr) {
        banks.push_back(
            Bank{id}
        );
        return SUCCESS;
    }
    return ALREADY_EXIST;
}

Status CentralBank::openAccont(std::string bank_id, std::string accont_id) {
    Bank* b = this->getBank(bank_id);
    if(b == nullptr) {return BANK_NOT_FOUND;}

    return b->openAccont(accont_id);
}


Status CentralBank::newMoney(std::string bank_id, std::string money_id, std::string money_symbol) {
    Bank* b = getBank(bank_id);
    if(b == nullptr) {return BANK_NOT_FOUND;}

    return b->moneyNew(money_id, money_symbol);
}


Status CentralBank::pay(
    std::string bank_id,
    cents value,
    std::string money_id,
    std::string from_id
) {
    Bank* b = getBank(bank_id);
    if(b == nullptr) {return BANK_NOT_FOUND;}

    Account* payer = b->getAccont(from_id);
    if(payer == nullptr) {return ACCOUNT_NOT_FOUND;}

    return b->pay(payer, value, money_id);
}

Status CentralBank::deposit(
    std::string bank_id,
    cents value,
    std::string money_id,
    std::string to_id
) {
    Bank* b = getBank(bank_id);
    if(b == nullptr) {return BANK_NOT_FOUND;}

    Account* receiver = b->getAccont(to_id);
    if(receiver == nullptr) {return ACCOUNT_NOT_FOUND;}

    return b->depositWhiteList(receiver, value, money_id);
}

Status CentralBank::transference(
    std::string bank_id,
    cents value,
    std::string money_id,
    std::string from_id,
    std::string to_id
) {
    Bank* b = getBank(bank_id);
    if(b == nullptr) {return BANK_NOT_FOUND;}

    Account* receiver = b->getAccont(to_id);
    if(receiver == nullptr) {return RECIEVER_NOT_FOUND;}

    Account* payer = b->getAccont(from_id);
    if(payer == nullptr) {return PAYER_NOT_FOUND;}

    const Money* m = payer->getMoney(money_id);

    return b->transference(payer, receiver, value, m->_mt.id, m->_mt.symbol);
}
