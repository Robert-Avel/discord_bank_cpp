#pragma once
#include "formater.hpp"
#include "sysbank.hpp"


//Interface de Comandos
namespace cmd
{
    FinalPayLoad open_bank(CentralBank* cb,std::string bank_id);
    FinalPayLoad open_accont(CentralBank* cb, std::string bank_id, std::string accont_id);
    FinalPayLoad bank_info(CentralBank* cb, std::string bank_id);
    FinalPayLoad account_info(CentralBank* cb, std::string bank_id, std::string accont_id);
    FinalPayLoad money_new(CentralBank* cb, std::string bank_id, std::string money_id, std::string money_symbol);
    FinalPayLoad money_info(CentralBank* cb, std::string bank_id, std::string money_id);
};
