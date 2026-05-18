#include "accont.hpp"
#include "base_payload.hpp"
#include "central_bank.hpp"
#include "client_manager.hpp"
#include <string>

class DiogoBotSys {
        /*
         * Link All accounts to their client to quick acess
         */
    void linkAccounts();

    public:
        CentralBank central_bank;
        ClientManager clients;

        DiogoBotSys(): central_bank(), clients() {};


        /*
         * @brief: Get a Client's account if the same is linked
         *
         * @param bank_id: Bank ID to get Account
         * @param bank_id: Client ID
         *
         * @return A pointer to that account, nullptr if not found or not linked
         */
        Account* getClientAccount(std::string& bank_id, std::string& client_id);

        BasePayLoad open_bank(std::string bank_id);
        BasePayLoad open_accont(std::string bank_id, std::string accont_id);
        BasePayLoad bank_info(std::string bank_id);
        BasePayLoad account_info(std::string bank_id, std::string accont_id);
        BasePayLoad money_new(std::string bank_id, std::string money_id, std::string money_symbol);
        BasePayLoad money_info(std::string bank_id, std::string money_id);
        BasePayLoad deposit(std::string bank_id, std::string user_id, std::string money_id, cents value);
        BasePayLoad pay(std::string bank_id, cents value, std::string money_id, std::string from_id);
        BasePayLoad transference(std::string bank_id, cents value, std::string money_id, std::string from_id, std::string to_id);

};
