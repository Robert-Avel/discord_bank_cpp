#include "client_user.hpp"
#include "accont.hpp"
#include "bank_status.hpp"


Status ClientUser::linkAccount(Account& a) {
    if(account != nullptr) {return ALREADY_EXIST;}

    this->account = &a;
    return SUCCESS;
}

/*
 * @brief Unlink with an account already created
 */
Status ClientUser::unlinkAccount() {
    if (account != nullptr) {
        account = nullptr;
        return SUCCESS;
    }
    return NOT_FOUND;
}
