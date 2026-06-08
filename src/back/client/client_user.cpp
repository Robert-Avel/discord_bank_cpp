#include "client_user.hpp"
#include "accont.hpp"
#include "status.hpp"
#include <sstream>


Status ClientUser::linkAccount(Account& a) {
    if(account != nullptr) {return ALREADY_EXIST;}

    this->account = &a;
    return SUCCESS;
}

Status ClientUser::unlinkAccount() {
    if (account != nullptr) {
        account = nullptr;
        return SUCCESS;
    }
    return NOT_FOUND;
}


std::string ClientUser::format() {
    std::stringstream buffer;

    buffer << user_id << "\n";
    if(this->account == nullptr) {
        buffer << account->getID() << "\n";
    }

    return buffer.str();
}



Status ClientUser::autoHire(std::string job_name, Money salary) {
    if(job.has_value()) {return ALREADY_EXIST;}

    job = ImprovisedJob{job_name, salary};
    return SUCCESS;
}


Status ClientUser::autoFire() {
    if(!job.has_value()) {return NO_JOB;}

    job.reset();
    return SUCCESS;
}


Status ClientUser::salaryPay() {
    if(!job.has_value()) {return NO_JOB;}

    if(account == nullptr) {return ACCOUNT_NOT_FOUND;}

    const Money& m = job.value().getSalary();

    updateLastSalay();
    return account->addMoney(m._mt.id, m._mt.symbol, m.value);
}
