#include "bank.hpp"
#include "bank_status.hpp"

Account* Bank::_getAccont(const std::string id) {
    for(Account& a: acconts) {
        if(id == a.getID()) {
            return &a;
        }
    }
    return nullptr;
}

Bank::Bank(std::string id) {this->id = id;}

std::string Bank::getID() const {return id;}
size_t Bank::getAccontN() const {return acconts.size();}

const Account* Bank::getAccont(const std::string id) {
    return _getAccont(id);
}


Status Bank::deposit(cents value, std::string money_id, std::string money_symbol, std::string to_id) {
    Account* target = this->_getAccont(to_id);
    if(target == nullptr) {return NOT_FOUND;}

    target->addMoney(money_id, money_symbol, value);
    return SUCCESS;
}


Status Bank::pay(cents value, std::string money_id, std::string money_symbol, std::string from_id) {
    Account* target = this->_getAccont(from_id);
    if(target == nullptr) {return NOT_FOUND;}

    if (target->removeMoney(money_id, value)) {
        return SUCCESS;
    }
    return NOT_ENOUGH_BALANCE;
}


Status Bank::openAccont(std::string id) {
    if(_getAccont(id) == nullptr) {
        acconts.push_back(
            Account{id}
        );
        return SUCCESS;
    }
    return ALREADY_EXIST;
}

Status Bank::transference(
    cents value,
    std::string money_id,
    std::string money_symbol,
    std::string from_id,
    std::string to_id
) {
    Account* to, *from;
    to = _getAccont(to_id);
    from = _getAccont(from_id);
    if(to == nullptr || from == nullptr) {return NOT_FOUND;}

    if (from->removeMoney(money_id, value)) {
        to->addMoney(money_id, money_symbol, value);
        return SUCCESS;
    }
    return NOT_ENOUGH_BALANCE;
}
