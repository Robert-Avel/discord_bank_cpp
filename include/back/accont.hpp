#pragma once
#include "bank_status.hpp"
#include "money.hpp"
#include <vector>


class Account {
    std::string id;
    std::vector<Money> balances;

    /**
     * @brief Busca internamente um ponteiro modificável para uma moeda específica.
     * @param money_id Identificador da moeda a ser localizada.
     * @return Ponteiro para o objeto Money correspondente, ou nullptr se não encontrado.
     */
    Money* _getMoney(std::string money_id);

    public:
    /**
     * @brief Construtor da classe Account.
     * @param id_ Identificador único da nova conta.
     */
    Account(std::string id_);

    /**
     * @brief Busca uma moeda específica para leitura (const).
     * @param money_id Identificador da moeda a ser localizada.
     * @return Ponteiro constante para o objeto Money correspondente.
     */
    const Money* getMoney(std::string money_id);

    /**
     * @brief Obtém o identificador único da conta.
     * @return String contendo o ID da conta.
     */
    std::string getID() const;

    /**
     * @brief Gera uma representação textual formatada de todos os saldos da conta.
     * @return String com os saldos formatados para exibição.
     */
    std::string formatBalance() const;

    /**
     * @brief Obtém a lista completa de saldos armazenados na conta.
     * @return Vetor constante contendo todos os objetos Money da conta.
     */
    const std::vector<Money> getBalances() const;

    /**
     * @brief Consulta o valor numérico do saldo de uma moeda específica em centavos.
     * @param money_id Identificador da moeda desejada.
     * @return Quantidade de centavos da moeda consultada.
     */
    const cents getBalance(std::string money_id);

    /**
     * @brief Adiciona ou deposita um valor em uma moeda específica na conta.
     * @param id Identificador da moeda.
     * @param symbol Símbolo monetário (ex: "R$", "$").
     * @param value Valor em centavos a ser adicionado.
     */
    void addMoney(std::string id, std::string symbol, cents value);

    /**
     * @brief Remove ou saca um valor em uma moeda específica da conta.
     * @param id Identificador da moeda.
     * @param value Valor em centavos a ser removido.
     * @return Status indicando o resultado da operação (ex: sucesso ou saldo insuficiente).
     */
    Status removeMoney(std::string id, cents value);
};
