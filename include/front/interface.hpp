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
};
