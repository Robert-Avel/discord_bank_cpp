#include "status.hpp"
#include "base_payload.hpp"
#include <map>
#include <vector>


#define CMD_BANK "banco"
#define CMD_USER "usuario"
#define CMD_ACCOUNT "conta"
#define CMD_JOB "emprego"
#define CMD_MONEY "moeda"


#define NEW_SUB_COMMAND(CMD, SUB_CMD) CMD "-" SUB_CMD


#define CMD_OPEN_BANK NEW_SUB_COMMAND(CMD_BANK, "abrir") //OK
#define CMD_OPEN_BANK_DESCRIPTION "Abra um novo banco neste servidor." //OK

#define CMD_INIT_USER NEW_SUB_COMMAND(CMD_USER, "iniciar")//OK
#define CMD_INIT_USER_DESCRIPTION "Inicia um usuario no servidor"//OK

#define CMD_INFO_BANK NEW_SUB_COMMAND(CMD_BANK, "info")//OK
#define CMD_INFO_BANK_DESCRIPTION "Informações do banco"//OK

#define CMD_INFO_ACCOUNT NEW_SUB_COMMAND(CMD_ACCOUNT, "info")//OK
#define CMD_INFO_ACCOUNT_DESCRIPTION "Informações da conta"//OK

#define CMD_NEW_MONEY NEW_SUB_COMMAND(CMD_MONEY, "novo")
#define CMD_NEW_MONEY_DESCRIPTION "Adiciona uma nova moeda"

#define CMD_INFO_MONEY NEW_SUB_COMMAND(CMD_MONEY, "info")
#define CMD_INFO_MONEY_DESCRIPTION "Informações da Moeda"

#define CMD_PAYMENT NEW_SUB_COMMAND(CMD_ACCOUNT, "pagar")
#define CMD_PAYMENT_DESCRIPTION "Saca um valor"

#define CMD_DEPOSIT NEW_SUB_COMMAND(CMD_ACCOUNT, "depositar")
#define CMD_DEPOSIT_DESCRIPTION "Deposita um valor na conta do usuário"

#define CMD_TRANSFERENCE NEW_SUB_COMMAND(CMD_ACCOUNT, "transferir")
#define CMD_TRANSFERENCE_DESCRIPTION "Trasfere um valor para um usuário"

#define CMD_HIRE_USER NEW_SUB_COMMAND(CMD_JOB, "contratar")
#define CMD_HIRE_USER_DESCRIPTION "Contrata um novo usuário para o sistema"

#define CMD_FIRE_USER NEW_SUB_COMMAND(CMD_JOB, "demitir")
#define CMD_FIRE_USER_DESCRIPTION "Demite um usuário do sistema"

#define CMD_PAY_CLIENT NEW_SUB_COMMAND(CMD_JOB, "salario")
#define CMD_PAY_CLIENT_DESCRIPTION "Paga um usuário pertencente ao sistema"


#define ARG_USER_NAME "nome-de-usuario"
#define ARG_USER_NAME_DESCRIPTION "O nome global"

#define ARG_USER_ID "identificador-de-usuario"
#define ARG_USER_ID_DESCRIPTION "Identificador do Usuário"

#define ARG_MONEY_VALUE "valor"
#define ARG_MONEY_VALUE_DESCRIPTION "O Valor da monetário da Operação"

#define ARG_MONEY_ID "id-da-moeda"
#define ARG_MONEY_ID_DESCRIPTION "O nome ou Identificador da moeda"

#define ARG_MONEY_SYMBOL "simbolo-da-moeda"
#define ARG_MONEY_SYMBOL_DESCRIPTION "O Simbolo da moeda"

#define ARG_RECEIVER_ID "id-destinatario"
#define ARG_RECEIVER_ID_DESCRIPTION "Identificador de quem vai receber"

#define ARG_PAYER_ID "id-pagador"
#define ARG_PAYER_ID_DESCRIPTION "Identificador de quem vai pagar"


#define ARG_JOB_NAME "nome-do-trabalho"
#define ARG_JOB_NAME_DESCRIPTION "O Nome do trabalho a ser atribuido"

using MsgKey = std::pair<Operation, Status>;


const std::map<PayloadType, std::vector<std::string>>
fields_PT = {
    {PL_TEXT, {"Obs:"}},
    {PL_MONEY_TYPE, {"ID", "Símbolo"}},
    {PL_MONEY, {"Saldo"}},
    {PL_BALANCE, {}},
    {PL_DEPOSIT, {"Moeda", "Valor", "Destinatário"}},
    {PL_PAY, {"Moeda", "Valor", "Remetente"}},
    {PL_TRANSFERENCE, {"Moeda", "Valor", "Remetente","Destinatário"}},
    {PL_BANK, {"ID", "Nº Contas"}},
    {PL_ACCOUNT, {"ID", "Saldo(s)"}},
    {PL_IMPROVISED_JOB, {"Cargo", "Salário"}},
    {PL_CLIENT, {"Nome", "ID", "ID do Banco", "Saldo(s)", "Emprego"}},
};


const std::map<Operation, std::string>
operation_PT = {
    {OPEN_BANK, "Abrir Banco"},
    {INIT_USER, "Abrir Conta"},
    {INFO_BANK, "Informaçôes do Banco"},
    {INFO_ACCOUNT, "Informaçôes da Conta"},
    {CHECK_BALANCE, "Saldo de Conta"},
    {NEW_MONEY, "Nova Moeda"},
    {INFO_MONEY, "Informação de Moeda"},
    {PAYMENT, "Pagamento"},
    {DEPOSIT, "Deposito"},
    {TRANSFERENCE, "Transferência"},
    {HIRE_USER, "Contratação"},
    {FIRE_USER, "Demissão"},
    {PAY_CLIENT, "Pagamento Salarial"}
};


const std::map<Status, std::string>
status_PT = {
    {Status::SUCCESS, "Sucesso"},
    {Status::NOT_FOUND, "Não Encontrado"},
    {Status::ALREADY_EXIST, "Já Existe"},
    {Status::NOT_ENOUGH_BALANCE, "Saldo Insuficiente"},
    {Status::FAILURE, "Falha Crítica"},
    {Status::MONEY_NOT_FOUND,"Moeda não encontrada"},
    {Status::ACCOUNT_NOT_FOUND,"Conta não encontrada"},
    {Status::BANK_NOT_FOUND,"Banco não encontrado"},
    {Status::RECIEVER_NOT_FOUND,"O Recebedor não foi encontrado"},
    {Status::PAYER_NOT_FOUND, "O Pagador não foi encontrado"},
    {Status::NO_JOB, "Cliente sem um Emprego atual"},
    {Status::CLIENT_NOT_FOUND, "Cliente não encontrado"},
    {Status::BALANCE_IN_MAX, "O Pagador não foi encontrado"},
    {Status::IN_COOLDOWN, "Aguarde..."}
};


const std::map<MsgKey, std::string>
messages_PT = {
    // --- OPEN_BANK ---
    {{OPEN_BANK, Status::SUCCESS},            "🏦 Um novo banco foi fundado com sucesso para este servidor."},
    {{OPEN_BANK, Status::ALREADY_EXIST},      "⚠️ Este servidor já possui um sistema bancário central estabelecido."},

    // --- OPEN_ACCONT ---
    {{INIT_USER, Status::SUCCESS},          "✅ Sua conta foi aberta! Bem-vindo ao sistema financeiro."},
    {{INIT_USER, Status::ALREADY_EXIST},    "🆔 Você já possui uma conta ativa em nosso banco."},
    {{INIT_USER, Status::BANK_NOT_FOUND},   "🚫 Não foi possível criar sua conta: Banco não encontrado."},


    // --- INFO_BANK ---
    {{INFO_BANK, Status::SUCCESS},            "📄Infomações do Banco"},
    {{INFO_BANK, Status::BANK_NOT_FOUND},     "🚫Banco não encontrado"},


    // --- INFO_ACCOUNT ---
    {{INFO_ACCOUNT, Status::SUCCESS},             "📄Infomações da Conta"},
    {{INFO_ACCOUNT, Status::BANK_NOT_FOUND},      "🚫Banco não encontrado"},
    {{INFO_ACCOUNT, Status::ACCOUNT_NOT_FOUND},   "🚫Conta não encontrado"},
    {{INFO_ACCOUNT, Status::CLIENT_NOT_FOUND},   "🚫Cliente não encontrado"},


    // --- NEW_COIN ---
    {{NEW_MONEY, Status::SUCCESS},             "🪙 Uma nova moeda foi registrada na economia do servidor."},
    {{NEW_MONEY, Status::ALREADY_EXIST},       "⚠️ Essa moeda já existe ou possui um símbolo duplicado."},
    {{NEW_MONEY, Status::BANK_NOT_FOUND},      "🚫 Erro: Autoridade bancária não encontrada para criar moedas."},


    {{INFO_MONEY, Status::SUCCESS},             "🪙 Informação da Moeda"},
    {{INFO_MONEY, Status::BANK_NOT_FOUND},      "🚫 O Banco nâo foi aberto neste servidor"},
    {{INFO_MONEY, Status::MONEY_NOT_FOUND},     "🚫 Moeda não encontrada"},


    // --- PAYMENT ---
    {{PAYMENT, Status::SUCCESS},              "💸 Pagamento processado! O destinatário já recebeu os fundos."},
    {{PAYMENT, Status::NOT_ENOUGH_BALANCE},   "⚠️ Saldo insuficiente para realizar este pagamento."},
    {{PAYMENT, Status::BANK_NOT_FOUND},       "🚫 O Banco nâo foi aberto neste servidor"},
    {{PAYMENT, Status::ACCOUNT_NOT_FOUND},    "🚫 Conta do Pagador não encontrado no sistema."},
    {{PAYMENT, Status::MONEY_NOT_FOUND},      "🚫 A Moeda utilizada na transação é Inválida."},

    // --- DEPOSIT ---
    {{DEPOSIT, Status::SUCCESS},              "📥 Depósito confirmado! O valor foi adicionado ao seu saldo seguro."},
    {{DEPOSIT, Status::ACCOUNT_NOT_FOUND},    "🚫 Conta de destino inexistente ou nâo foi encontada"},
    {{DEPOSIT, Status::MONEY_NOT_FOUND},      "🚫 Moeda não encontrada"},
    {{DEPOSIT, Status::BANK_NOT_FOUND},       "🚫 O Banco nâo foi aberto neste servidor"},
    {{PAYMENT, Status::BALANCE_IN_MAX},       "🚫 O Saldo chegou ao limite possivel."},


    // --- TRANSFERENCE ---
    {{TRANSFERENCE, Status::SUCCESS},               "📲 Transferência realizada com sucesso entre contas."},
    {{TRANSFERENCE, Status::NOT_ENOUGH_BALANCE},    "⚠️ Saldo insuficiente para completar a transferência."},
    {{TRANSFERENCE, Status::BANK_NOT_FOUND},        "🚫 O Banco nâo foi aberto neste servidor"},
    {{TRANSFERENCE, Status::RECIEVER_NOT_FOUND},    "🚫 Conta de destino inexistente ou nâo foi encontada"},
    {{TRANSFERENCE, Status::PAYER_NOT_FOUND},       "🚫 Conta do Pagador não encontrado no sistema."},
    {{TRANSFERENCE, Status::MONEY_NOT_FOUND},       "🚫 Moeda não encontrada"},
    {{TRANSFERENCE, Status::BALANCE_IN_MAX},        "🚫 O Saldo chegou ao limite possivel."},
    {{TRANSFERENCE, Status::FAILURE},               "🚫 Falha Crítica"},


    // --- HIRE USERE ---
    {{HIRE_USER, Status::BANK_NOT_FOUND},        "🚫 O Banco nâo foi aberto neste servidor"},
    {{HIRE_USER, Status::CLIENT_NOT_FOUND},      "🚫 O Cliente nâo foi encontrado neste servidor"},
    {{HIRE_USER, Status::MONEY_NOT_FOUND},       "🚫 Moeda não encontrada"},
    {{HIRE_USER, Status::ALREADY_EXIST},         "🚫 O Cliente já possui um Emprego"},
    {{HIRE_USER, Status::SUCCESS},               "📝 Novo emprego Adquirido, agora você é quase um CLT"},

    // --- FIRE USERE ---
    {{FIRE_USER, Status::BANK_NOT_FOUND},        "🚫 O Banco nâo foi aberto neste servidor"},
    {{FIRE_USER, Status::CLIENT_NOT_FOUND},      "🚫 O Cliente nâo foi encontrado neste servidor"},
    {{FIRE_USER, Status::NO_JOB},                "🚫 O Cliente não possui um Emprego"},
    {{FIRE_USER, Status::SUCCESS},               "📝 O Cliente já possui um Emprego"},

    // --- PAY CLIENT ---
    {{PAY_CLIENT, Status::BANK_NOT_FOUND},        "🚫 O Banco nâo foi aberto neste servidor"},
    {{PAY_CLIENT, Status::CLIENT_NOT_FOUND},      "🚫 O Cliente nâo foi encontrado neste servidor"},
    {{PAY_CLIENT, Status::NO_JOB},                "🚫 O Cliente não possui um Emprego"},
    {{PAY_CLIENT, Status::ACCOUNT_NOT_FOUND},     "🚫 Conta do cliente inexistente ou nâo foi encontada"},
    {{PAY_CLIENT, Status::BALANCE_IN_MAX},        "🚫 O Saldo chegou ao limite possivel."},
    {{PAY_CLIENT, Status::IN_COOLDOWN},        "🚫 Você já resgatou o salário hoje, Aguarde até a proxima data."},
    {{PAY_CLIENT, Status::SUCCESS},               "📥 Depósito confirmado! O valor foi adicionado ao seu saldo seguro."},


};
