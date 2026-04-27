#include "bank.cpp"
#include "payload.hpp"
#include <string>

static std::string
operation_PT[] = {
    "Abrir Banco",
    "Abrir Conta",
    "Saldo de Conta",
    "Nova Moeda",
    "Pagamento",
    "Deposito",
    "Transferência"
};


static std::string
status_PT[] = {
    "Sucesso",
    "Não Encontrado",
    "Já Existe",
    "Saldo Insuficiente"
};


namespace bank {
    PayLoad
    openBank(CentralBank* b, std::string id) {
        if(b->openBank(id) == SUCCESS) {
            return PayLoad{
                operation_PT[0],
                status_PT[0],
                "Um novo banco foi aberto para este servidor",
                "ID",
                (b->getBank(id)->getID())
            };
        }
        return PayLoad{
            operation_PT[0],
            status_PT[2],
            "Já Existe um banco aberto neste servidor",
            "ID",
            (b->getBank(id)->getID())
        };
    }
};
