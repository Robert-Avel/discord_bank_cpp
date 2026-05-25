#include "status.hpp"
#include "base_payload.hpp"
#include <map>
#include <vector>

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
    {PL_CLIENT, {"Nome", "ID", "ID do Banco", "Saldo(s)"}},
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
    {Status::BALANCE_IN_MAX, "O Pagador não foi encontrado"}
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
    {{PAY_CLIENT, Status::SUCCESS},               "📥 Depósito confirmado! O valor foi adicionado ao seu saldo seguro."},


};
