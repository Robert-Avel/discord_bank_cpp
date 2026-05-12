#include "client_user.hpp"
#include "bank_status.hpp"


Status ClientUser::linkAccount(uint32_t index) {
    if(account_index.has_value()) {return ALREADY_EXIST;}

    this->account_index = index;
    return SUCCESS;
}

/*
 * @brief Unlink with an account already created
 */
Status ClientUser::unlinkAccount() {
    if (account_index.has_value()) {
        account_index.reset();
        return SUCCESS;
    }
    return NOT_FOUND;
}


ClientUser::~ClientUser() {
    unlinkAccount();
}
