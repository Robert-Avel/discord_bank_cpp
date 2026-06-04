#include "bank.hpp"
#include "accont.hpp"
#include "client_user.hpp"
#include "status.hpp"
#include "money.hpp"


Account* Bank::getAccont(const std::string id) const {
    for(const Account& a: acconts) {
        if(id == a.getID()) {
            return const_cast<Account*>(&a);
        }
    }
    return nullptr;
}


Status Bank::deposit(Account* to, cents value, std::string money_id, std::string money_symbol) {
    if(to == nullptr) {return RECIEVER_NOT_FOUND;}


    return to->addMoney(money_id, money_symbol, value);
}


Status Bank::depositWhiteList(Account* to, cents value, std::string money_id) {
    MoneyType* money = this->getMoney(money_id);
    if(to == nullptr) {return RECIEVER_NOT_FOUND;}
    if(money == nullptr) {return MONEY_NOT_FOUND;}

    return to->addMoney(money->id, money->symbol, value);
}


Status Bank::pay(Account* from, cents value, std::string money_id) {
    if(from == nullptr) {return PAYER_NOT_FOUND;}

    return from->removeMoney(money_id, value);
}


Status Bank::openAccont(std::string id) {
    if(getAccont(id) == nullptr) {
        acconts.push_back(
            Account{id}
        );
        return SUCCESS;
    }
    return ALREADY_EXIST;
}


Status Bank::loadAccount(const Account& a) {
    if(a.getID().empty()) {return FAILURE;}
    this->acconts.push_back(a);
    return SUCCESS;
}


Status Bank::transference(
    Account* from,
    Account* to,
    cents value,
    std::string money_id,
    std::string money_symbol
) {
    if(from == nullptr) {return PAYER_NOT_FOUND;}
    if(to == nullptr) {return RECIEVER_NOT_FOUND;}

    Status s = from->removeMoney(money_id, value);


    if (s == SUCCESS) {
        return to->addMoney(money_id, money_symbol, value);
    }
    return s;
}


Status Bank::moneyNew(std::string id, std::string symbol) {
    for (MoneyType& m: white_list_money) {
        if(m.id == id || m.symbol == symbol) {
            return ALREADY_EXIST;
        }
    }
    white_list_money.push_back({id, symbol});
    return SUCCESS;
}


MoneyType* Bank::getMoney(std::string id) {
    if(white_list_money.empty()) {return nullptr;}

    for(MoneyType& m: white_list_money) {
        if(m.id == id) {
            return &m;
        }
    }
    return nullptr;
}



Status Bank::newClient(const std::string& id, const std::string& global_name) {
    Status s = clients.newClient(global_name, id);
    if(s != SUCCESS) {return s;}

    s = openAccont(id);
    if(s != SUCCESS) {return s;}

    return linkAccount(id);
}


Status Bank::linkAccount(const std::string& id) {
    Account* a = getAccont(id);
    if (a == nullptr) {return ACCOUNT_NOT_FOUND;}

    ClientUser* c = clients.getClient(id);
    if (c == nullptr) {return CLIENT_NOT_FOUND;}

    return c->linkAccount(*a);
}
