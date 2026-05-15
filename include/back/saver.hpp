#include "accont.hpp"
#include "bank.hpp"
#include "central_bank.hpp"
#include "money.hpp"
#include <fstream>


namespace save {
    bool money_type(const MoneyType& mt, std::ofstream& file);
    bool money(const Money& m, std::ofstream& file);
    bool account(const Account& c, std::ofstream& file);
    bool bank(const Bank& b, std::ofstream& file);
    bool central_bank(const CentralBank& cb, std::ofstream& file);
}


namespace load{
    MoneyType money_type(std::ifstream& file);
    Money money(std::ifstream& file);
    Account account(std::ifstream& file);
    Bank bank(std::ifstream& file);
    CentralBank central_bank(std::ifstream& file);

}
