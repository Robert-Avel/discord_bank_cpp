#pragma once
#include "formater.hpp"
#include "sysbank.hpp"


//Interface de Comandos
namespace cmd
{
    FinalPayLoad openbank(CentralBank* cb,std::string bank_id);
    FinalPayLoad openaccont(CentralBank* cb, std::string bank_id, std::string accont_id);
};
