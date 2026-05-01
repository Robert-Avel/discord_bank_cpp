#include "interface.hpp"
#include "accont.hpp"
#include "bank_status.hpp"
#include "base_payload.hpp"
#include "sysbank.hpp"
#include <sstream>

//Interface de Comandos

FinalPayLoad cmd::open_bank(CentralBank* cb,std::string bank_id) {
    Status result = cb->openBank(bank_id);
    const Bank* b = cb->getBank(bank_id);
    if (result == SUCCESS) {
        return FinalPayLoad({OPEN_BANK, SUCCESS, payload::Bank{b->getID(), b->getAccontN()}});
    } else {
        return FinalPayLoad({OPEN_BANK, ALREADY_EXIST, bank_id});
    }
}


FinalPayLoad cmd::open_accont(CentralBank* cb, std::string bank_id, std::string accont_id) {
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

FinalPayLoad cmd::bank_info(CentralBank* cb, std::string bank_id) {
    Bank* b = cb->getBank(bank_id);
    if (b == nullptr) {
        return FinalPayLoad({INFO_BANK, NOT_FOUND, bank_id});
    }
    return FinalPayLoad({INFO_BANK, NOT_FOUND, payload::Bank{b->getID(), b->getAccontN()}});
}


FinalPayLoad cmd::account_info(CentralBank* cb, std::string bank_id, std::string accont_id) {
    Bank* b = cb->getBank(bank_id);

    std::stringstream buffer;

    if (b == nullptr) {
        buffer << "Bank: " << bank_id;
        return FinalPayLoad({INFO_ACCOUNT, NOT_FOUND, buffer.str()});
    }

    const Account* a = b->getAccont(accont_id);
    if (a == nullptr) {
        buffer << "Account: " << accont_id;
        return FinalPayLoad({INFO_ACCOUNT, NOT_FOUND, buffer.str()});
    }

    return FinalPayLoad({INFO_ACCOUNT, SUCCESS,
        payload::Account{accont_id, a->formatBalance()}
    });
}
