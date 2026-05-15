#include "client_user.hpp"
#include "accont.hpp"
#include "bank_status.hpp"


Status ClientUser::linkAccount(Account& a, const std::string& bank_id) {
    if(getAccount(bank_id) == nullptr) {return ALREADY_EXIST;}

    this->accounts[bank_id] = a;
    return SUCCESS;
}

/*
 * @brief Unlink with an account already created
 */
Status ClientUser::unlinkAccount(const std::string& bank_id) {
    auto it = accounts.find(bank_id);
    if(it == accounts.end()) {return NOT_FOUND;}

    accounts.erase(it);
    return SUCCESS;
}
