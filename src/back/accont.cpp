#include "accont.hpp"
#include "money.hpp"
#include <algorithm>
#include <sstream>

Money* Account::_getMoney(std::string money_id) {
    auto getter = balances.begin();
    while (getter != balances.end()) {
        if(getter->_mt.id == money_id) {
            return &*getter;
        }
        getter++;
    }
    return nullptr;
}

Account::Account(std::string id_): balances() {
    this->id = id_;
}

std::string Account::getID() const {return id;}

const std::vector<Money> Account::getBalances() const {return balances;}


const cents Account::getBalance(std::string money_id) {
    Money* money = _getMoney(money_id);
    if (money == nullptr) {return 0;}
    return money->value;
}

void Account::addMoney(std::string id, std::string symbol, cents value) {
    Money* money = _getMoney(id);
    if (money == nullptr) {
        balances.push_back(
            Money{  MoneyType{id, symbol},  value}
        );
    } else {
        money->value += value;
    }
}

bool Account::removeMoney(std::string id, cents value) {
    auto balance = _getMoney(id);
    if (balance == nullptr) {
        return false;
    }

    if (balance->value > value) {
        balance->value -= value;
    }
    else if (balance->value == value) {
        auto remove = std::remove_if(
            balances.begin(), balances.end(),
            [&id](Money& m) {return id == m._mt.id;}
        );

        balances.erase(remove);
    }
    else {return false;}

    return true;
}


std::string Account::formatBalance() const {
    if (this->balances.empty()) {
        return "0";
    }
    std::stringstream buffer;
    for(const Money& m: this->balances) {
        buffer << m.format() << "\n";
    }
    return buffer.str();
}
