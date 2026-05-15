#include "central_bank.hpp"
#include "client_manager.hpp"

class DiogoBotSys {
    CentralBank central_bank;
    ClientManager clients;

    public:
        DiogoBotSys(): central_bank(), clients() {};
};
