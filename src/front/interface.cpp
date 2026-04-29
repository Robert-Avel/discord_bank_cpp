#include "interface.hpp"
#include "sysbank.hpp"

//Interface de Comandos

FinalPayLoad cmd::openbank(CentralBank* cb,std::string bank_id) {
    Status result = cb->openBank(bank_id);
    if (result == SUCCESS) {
        return FinalPayLoad({OPEN_BANK, SUCCESS, bank_id});
    } else {
        return FinalPayLoad({OPEN_BANK, ALREADY_EXIST, bank_id});
    }
}


FinalPayLoad cmd::openaccont(CentralBank* cb, std::string bank_id, std::string accont_id) {
    Bank* b = cb->getBank(bank_id);
    if (b == nullptr) {
        return FinalPayLoad({OPEN_ACCONT, NOT_FOUND, bank_id});
    }
    Status result = b->openAccont(accont_id);
    if (result == SUCCESS) {
        return FinalPayLoad({OPEN_ACCONT, SUCCESS, accont_id});
    } else {
        return FinalPayLoad({OPEN_ACCONT, ALREADY_EXIST, accont_id});
    }
}
