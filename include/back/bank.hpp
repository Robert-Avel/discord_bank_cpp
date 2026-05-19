#pragma once
#include "accont.hpp"
#include "bank_status.hpp"
#include "client_manager.hpp"
#include "client_user.hpp"
#include "money.hpp"


class Bank {
    std::string id;
    std::vector<Account> acconts;
    std::vector<MoneyType> white_list_money;
    ClientManager clients;

    public:
    Bank(std::string id) {this->id = id;}
    /*
    @brief Obtém o ID único do banco.

    @return Uma string contendo o ID do banco.
    */
    std::string getID() const {return id;}

    /*
    @brief Obtém o número de contas no banco.

    @return O tamanho do vetor de contas (size_t).
    */
    size_t getAccontN() const {return acconts.size();}

    /*
    @brief Busca uma conta pelo seu ID.

    @param id O ID da conta a ser procurada.

    @return Ponteiro para a conta se encontrada; caso contrário, retorna nullptr.
    */
    Account* getAccont(const std::string id);

    /*
    @brief Obtém uma cópia constante do vetor de todas as contas.

    @return Um vetor constante de objetos Account.
    */
    std::vector<Account> getAccounts() const {return acconts;}

    /*
    @brief Obtém uma cópia constante do vetor de moedas na lista branca.

    @return Um vetor constante de objetos MoneyType.
    */
    const std::vector<MoneyType> getWhiteListMoney() const {return white_list_money;}

    /*
    @brief Cria um novo tipo de moeda e o adiciona à lista branca.

    @param id O ID único para a nova moeda.
    @param symbol O símbolo da nova moeda (ex: "USD").

    @return Um objeto Status indicando o sucesso ou falha da operação.
    */
    Status moneyNew(std::string id, std::string symbol);

    /*
    @brief Busca um tipo de moeda pelo seu ID.

    @param id O ID da moeda a ser procurada.

    @return Ponteiro para o MoneyType se encontrado; caso contrário, retorna nullptr.
    */
    MoneyType* getMoney(std::string id);


    /*
    @brief Abre uma nova conta no banco.

    @param id O ID único para a nova conta.

    @return Um objeto Status indicando o sucesso ou falha da operação.
    */
    Status openAccont(std::string id);

    /*
    @brief Deposita um valor em uma conta usando um tipo de moeda específico.

    @param to Ponteiro para a conta de destino.
    @param value O valor em centavos a ser depositado.
    @param money_id O ID do tipo de moeda.
    @param money_symbol O símbolo da moeda (para validação).

    @return Um objeto Status indicando o sucesso ou falha da operação.
    */
    Status deposit(Account* to, cents value, std::string money_id, std::string money_symbol);

    /*
    @brief Deposita um valor em uma conta usando uma moeda da lista branca.

    @param to Ponteiro para a conta de destino.
    @param value O valor em centavos a ser depositado.
    @param money_id O ID do tipo de moeda (deve estar na white_list).

    @return Um objeto Status indicando o sucesso ou falha da operação.
    */
    Status depositWhiteList(Account* to, cents value, std::string money_id);

    /*
    @brief Realiza um pagamento (saque) de uma conta.

    @param from Ponteiro para a conta de origem.
    @param value O valor em centavos a ser pago.
    @param money_id O ID do tipo de moeda.

    @return Um objeto Status indicando o sucesso ou falha da operação.
    */
    Status pay(Account* from, cents value, std::string money_id);

    /*
    @brief Realiza uma transferência entre duas contas.

    @param from Ponteiro para a conta de origem.
    @param to Ponteiro para a conta de destino.
    @param value O valor em centavos a ser transferido.
    @param money_id O ID do tipo de moeda.
    @param money_symbol O símbolo da moeda (para validação).

    @return Um objeto Status indicando o sucesso ou falha da operação.
    */
    Status transference(
        Account* from,
        Account* to,
        cents value,
        std::string money_id,
        std::string money_symbol
    );

    /*
    @brief Carrega uma conta existente no banco.

    @param a Uma referência constante ao objeto Account a ser carregado.

    @return Um objeto Status indicando o sucesso ou falha da operação.
    */
    Status loadAccount(const Account& a);


    Status newClient(const std::string& id, const std::string& global_name) {
        return clients.newClient(global_name, id);
    }

    ClientUser* getClient(const std::string& id) {
        return clients.getClient(id);
    }

};
