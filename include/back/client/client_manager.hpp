#pragma once
#include "status.hpp"
#include "client_user.hpp"
#include <vector>


/*
 * A Class that manage many clients of banks
 */
class ClientManager {
    std::vector<ClientUser> clients;


    public:
    ClientManager() = default;

    /*
     * @brief Directy Load a ClientUser object
     */
    Status loadClient(const ClientUser& c);

    /*
     * @brief Create a new Client for Manager
     *
     * @param bank_id: Defines the bank ID of which the account belong to
     * @param global_name: Defines the global name used in interface
     * @param user_id: Unique ID for internal identification
     *
     * @returns the Status of Operation (SUCESS || ALREADY_EXIST)
     */
    Status newClient(const std::string& global_name, const  std::string& id);


    /*
     * @brief Get a client from the ID
     *
     * @param id: the ID of client
     *
     * @return A pointer to the Client User, or nullptr if not found
     */
    ClientUser* getClient(const std::string& id) const;

    /*Get a Iterator of Clients from begin */
    std::vector<ClientUser>& getAllClient() {return clients;}


    /*
     * @brief Remove a client from the ID
     *
     * @param id: the ID of client
     *
     * @return Status of operation (SUCESS || NOT_FOUND)
     */
    Status removeClient(const std::string& id);
};
