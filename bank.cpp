//USANDO UM JOGO DE DINHEIRO COMO EXEMPLO
#include <algorithm>
#include <string>
#include <vector>
#include "payload.hpp"

enum Status {
    SUCCESS,
    ALREADY_EXIST,
    NOT_FOUND,
    NOT_ENOUGH_BALANCE
};


enum Action {
    CREATE,
    DELETE,
    EDIT,
    SELECT,
    DEPOSIT,
    PAY,
    TRANSFER
};


enum Target {
    MONEY,
    BANK,
    ACCOUNT
};


enum PayloadType {
    P_MONEY,
    P_BANK,
    P_ACCOUNT,
    P_PRIMAL_DEPOSIT,
    P_DEPOSTIT,
    P_WITHDRAW,
    P_TRANSFER,
    P_ID,
    P_MONEY_VALUE
};


class Account {
    std::string id;
    std::vector<Money> balances;


    Money* _getMoney(std::string money_id) {
        auto getter = balances.begin();
        while (getter != balances.end()) {
            if(getter->_mt.id == money_id) {
                return &*getter;
            }
            getter++;
        }
        return nullptr;
    }

    public:
    Account(std::string id_): balances() {
        this->id = id_;
    }

    std::string getID() {return id;}

    cents getBalance(std::string money_id) {
        Money* money = _getMoney(money_id);
        if (money == nullptr) {return 0;}
        return money->value;
    }

    void addMoney(std::string id, std::string symbol, cents value) {
        Money* money = _getMoney(id);
        if (money == nullptr) {
            balances.push_back(
                Money{  MoneyType{id, symbol},  value}
            );
        } else {
            money->value += value;
        }
    }

    bool removeMoney(std::string id, cents value) {
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
};


class Bank {
    std::string id;
    std::vector<Account> acconts;
    std::vector<MoneyType> white_list_money;

    Account* _getAccont(const std::string id) {
        for(Account& a: acconts) {
            if(id == a.getID()) {
                return &a;
            }
        }
        return nullptr;
    }

    public:
    Bank(std::string id) {this->id = id;}

    std::string getID() {return id;}

    Account* getAccont(const std::string id) {
        return _getAccont(id);
    }


    Status deposit(cents value, std::string money_id, std::string money_symbol, std::string to_id) {
        Account* target = this->_getAccont(to_id);
        if(target == nullptr) {return NOT_FOUND;}

        target->addMoney(money_id, money_symbol, value);
        return SUCCESS;
    }

    Status deposit(payload::Deposit& d) {
        return this->deposit(
            d.value,
            d.mt_.id, d.mt_.symbol,
            d.to_id
        );
    }

    Status pay(cents value, std::string money_id, std::string money_symbol, std::string from_id) {
        Account* target = this->_getAccont(from_id);
        if(target == nullptr) {return NOT_FOUND;}

        if (target->removeMoney(money_id, value)) {
            return SUCCESS;
        }
        return NOT_ENOUGH_BALANCE;
    }

    Status pay(payload::Pay& p) {
        return this->pay(
            p.value,
            p.mt_.id, p.mt_.symbol,
            p.from_id
        );
    }


    bool openAccont(std::string id) {
        if(_getAccont(id) == nullptr) {
            acconts.push_back(
                Account{id}
            );
            return true;
        }
        return false;
    }

    Status transference(
        cents value,
        std::string money_id,
        std::string money_symbol,
        std::string from_id,
        std::string to_id
    ) {
        Account* to, *from;
        to = getAccont(to_id);
        from = getAccont(from_id);
        if(to == nullptr || from == nullptr) {return NOT_FOUND;}

        if (from->removeMoney(money_id, value)) {
            to->addMoney(money_id, money_symbol, value);
            return SUCCESS;
        }
        return NOT_ENOUGH_BALANCE;
    }
};


class CentralBank {
    std::vector<Bank> banks;

    public:
    CentralBank(): banks() {}

    Bank* getBank(std::string id) {
        for(Bank& b: banks) {
            if(b.getID() == id) {
                return &b;
            }
        }
        return nullptr;
    }

    Status openBank(std::string id) {
        if(getBank(id) == nullptr) {
            banks.push_back(
                Bank{id}
            );
            return SUCCESS;
        }
        return ALREADY_EXIST;
    }
};
