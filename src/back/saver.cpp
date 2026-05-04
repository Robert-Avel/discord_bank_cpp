#include "saver.hpp"
#include "accont.hpp"
#include "money.hpp"
#include <cstdint>
#include <vector>
#include <iostream>


bool save::money_type(const MoneyType& mt, std::ofstream& file) {
    if (!file) {
        std::cerr << "Error: File stream is not open or is in an error state.\n";
        return false;
    }

    uint32_t id_size = mt.id.size();
    file.write( (char*) &id_size, sizeof(uint32_t));
    file.write( (char*) mt.id.c_str(), id_size);

    uint32_t symbol_size = mt.symbol.size();
    file.write( (char*) &symbol_size, sizeof(uint32_t));
    file.write( (char*) mt.symbol.c_str(), symbol_size);

    return true;
}

bool save::money(const Money& m, std::ofstream& file) {
    if (!file) {
        std::cerr << "Error: File stream is not open or is in an error state.\n";
        return false;
    }
    file.write((char*) &m.value, sizeof(uint32_t));
    save::money_type(m._mt, file);

    return true;
}

bool save::account(const Account& c, std::ofstream& file) {
    if (!file) {
        std::cerr << "Error: File stream is not open or is in an error state.\n";
        return false;
    }



    const uint32_t id_size = c.getID().size();
    file.write( (char*) &id_size, sizeof(uint32_t));
    file.write( (char*) c.getID().c_str(), id_size);

    const std::vector<Money> balance = c.getBalances();
    uint32_t balance_size = balance.size();
    file.write((char*) &balance_size, sizeof(uint32_t));

    for(const Money& m: balance) {
        save::money(m, file);
    }

    return true;
}

bool save::bank(const Bank& b, std::ofstream& file) {
    if (!file) {
        std::cerr << "Error: File stream is not open or is in an error state.\n";
        return false;
    }
    uint32_t bank_id_size = b.getID().size();
    file.write( (char*) &bank_id_size, sizeof(uint32_t));
    file.write( (char*) b.getID().c_str(), bank_id_size);

    std::vector<Account> _accounts = b.getAccounts();
    uint32_t accont_n = b.getAccontN();
    file.write((char*) &accont_n, sizeof(uint32_t));

    for(const Account& a: _accounts) {
        save::account(a, file);
    }

    std::vector<MoneyType> _white_list_m = b.getWhiteListMoney();
    uint32_t _white_list_m_n = _white_list_m.size();
    file.write((char*) &_white_list_m_n, sizeof(uint32_t));
    if (_white_list_m_n > 0) {
        for(const MoneyType& mt: _white_list_m) {
            save::money_type(mt, file);
        }
    }

    return true;
}


MoneyType load::money_type(std::ifstream& file) {
    if (!file) {
        return MoneyType{"", ""};
    }

    uint32_t id_size;
    file.read((char*) &id_size, sizeof(uint32_t));
    std::string id(id_size, '\0');
    file.read((char*) id.data(), id_size);

    uint32_t symbol_size;
    file.read((char*) &symbol_size, sizeof(uint32_t));
    std::string symbol(symbol_size, '\0');
    file.read((char*) symbol.data(), symbol_size);

    return MoneyType{id, symbol};
}


Money load::money(std::ifstream& file) {
    if (!file) {
        return Money{{"", ""}, 0};
    }


    uint32_t value;
    file.read((char*) &value, sizeof(uint32_t));
    MoneyType mt = load::money_type(file);

    return Money{mt, value};
}


Account load::account(std::ifstream& file) {
    if (!file) {
        return Account{""};
    }

    uint32_t id_size;
    file.read( (char*) &id_size, sizeof(uint32_t));
    std::string id(id_size, '\0');
    file.read( (char*) id.data(), id_size);

    Account account{id};

    uint32_t balance_size;
    file.read((char*) &balance_size, sizeof(uint32_t));

    for(uint32_t i = 0; i < balance_size; i++) {
        Money m = load::money(file);
        account.addMoney(m._mt.id, m._mt.symbol, m.value);
    }

    return account;
}


Bank load::bank(std::ifstream& file) {
    if (!file) {
        return Bank{""};
    }

    uint32_t bank_id_size;
    file.read( (char*) &bank_id_size, sizeof(uint32_t));

    std::string id(bank_id_size, '\0');
    file.read( (char*) id.data(), bank_id_size);

    Bank bank{id};

    uint32_t accont_n;
    file.read( (char*) &accont_n, sizeof(uint32_t));

    for(uint32_t i = 0; i < accont_n; i++) {
        Account a = load::account(file);
        bank.loadAccount(a);
    }

    uint32_t _white_list_m_n;
    file.read( (char*) &_white_list_m_n, sizeof(uint32_t));

    for(uint32_t i = 0; i < _white_list_m_n; i++) {
        MoneyType mt = load::money_type(file);
        bank.moneyNew(mt.id, mt.symbol);
    }

    return bank;
}
