
#include "client_manager.hpp"
#include "status.hpp"
#include "client_user.hpp"
#include <algorithm>


Status ClientManager::newClient(const std::string& global_name, const  std::string& id) {
    auto c = ClientUser(global_name, id);
    return loadClient(c);
}


Status ClientManager::loadClient(const ClientUser& c) {
    if (getClient(c.getUserID()) != nullptr) {return ALREADY_EXIST;}

    clients.push_back(c);
    return SUCCESS;
}

ClientUser* ClientManager::getClient(const std::string& id) {
    auto get = std::find_if(clients.begin(), clients.end(),
        [&id](ClientUser& c) {return c.getUserID() == id;});

    if (get == clients.end()) {return nullptr;}
    return &*get;
}

Status ClientManager::removeClient(const std::string& id) {
    auto get = std::find_if(clients.begin(), clients.end(),
        [&id](ClientUser& c) {return c.getUserID() == id;});

    if (get == clients.end()) {return NOT_FOUND;}

    clients.erase(get);
    return SUCCESS;
}
