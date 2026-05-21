#pragma once
#include <optional>
#include <string>
#include "accont.hpp"
#include "bank_status.hpp"
#include "job.hpp"

/*
 * @Client User of SysBank, represent the users of a Bank within CentralBank
 */
class ClientUser {
    std::string global_name;

    std::string user_id;
    std::string bank_id;
    Account* account;

    std::optional<ImprovisedJob> job;


    public:

    /*
     * @brief Base Constructor of Client User Class
     *
     * @param bank_id: Defines the bank ID of which the account belong to
     * @param global_name: Defines the global name used in interface
     * @param user_id: Unique ID for internal identification
     */
    ClientUser(const std::string& global_name, const  std::string& user_id): user_id(user_id) {
        this->global_name = global_name;
        this->account = nullptr;
    }

    /*
     * Returns the Global Name of Client
     */
    const std::string& getGlobalName() const {return this->global_name;}

    /*
     * Returns the User ID of Client
     */
    const std::string& getUserID() const {return this->user_id;}

    /*
     * Returns the Bank ID of Bank
     */
    const std::string& getBankID() const {return this->bank_id;}

    /*
     * Returns a pointer of the index of its account in Bank, returns nullptr if the client has no account
     */
    Account* getAccount() const {
        return account;
    }


    /*
     * @brief After the creation of an account, it may be linked with the Client, allowing fast acess
     *
     * @param a: Account object
     */
    Status linkAccount(Account& a);

    /*
     * @brief Unlink with an account already created
     */
    Status unlinkAccount();

    /*
     * @brief Set a new Global Name
     *
     * @param new_g_n: New Global Name to set
     */
    void setGlobalName(const std::string& new_g_n) {this->global_name = new_g_n;}


    std::string format();


    const ImprovisedJob* getJob() const {
        if(!job.has_value()) {return nullptr;} return &job.value();
    }


    Status autoHire(std::string job_name, Money salary) {
        if(job.has_value()) {return ALREADY_EXIST;}

        job = ImprovisedJob{job_name, salary};
        return SUCCESS;
    }


    Status autoFire() {
        if(!job.has_value()) {return NO_JOB;}

        job.reset();
        return SUCCESS;
    }


    Status salaryPay() {
        if(!job.has_value()) {return NO_JOB;}

        if(account == nullptr) {return ACCOUNT_NOT_FOUND;}

        const Money& m = job.value().getSalary();

        account->addMoney(m._mt.id, m._mt.symbol, m.value);
        return SUCCESS;
    }



};
