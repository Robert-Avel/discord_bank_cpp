#include "bank_status.hpp"
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
};


const std::map<Operation, std::string>
operation_PT = {
    {OPEN_BANK, "Abrir Banco"},
    {OPEN_ACCONT, "Abrir Conta"},
    {INFO_BANK, "Informaçôes do Banco"},
    {INFO_ACCOUNT, "Informaçôes da Conta"},
    {CHECK_BALANCE, "Saldo de Conta"},
    {NEW_MONEY, "Nova Moeda"},
    {INFO_MONEY, "Informação de Moeda"},
    {PAYMENT, "Pagamento"},
    {DEPOSIT, "Deposito"},
    {TRANSFERENCE, "Transferência"}
};


const std::map<Status, std::string>
status_PT = {
    {Status::SUCCESS, "Sucesso"},
    {Status::NOT_FOUND, "Não Encontrado"},
    {Status::ALREADY_EXIST, "Já Existe"},
    {Status::NOT_ENOUGH_BALANCE, "Saldo Insuficiente"}
};


const std::map<MsgKey, std::string>
messages_PT = {
    // --- OPEN_BANK ---
    {{OPEN_BANK, Status::SUCCESS},            "🏦 Um novo banco foi fundado com sucesso para este servidor."},
    {{OPEN_BANK, Status::ALREADY_EXIST},      "⚠️ Este servidor já possui um sistema bancário central estabelecido."},

    // --- OPEN_ACCONT ---
    {{OPEN_ACCONT, Status::SUCCESS},          "✅ Sua conta foi aberta! Bem-vindo ao sistema financeiro."},
    {{OPEN_ACCONT, Status::ALREADY_EXIST},    "🆔 Você já possui uma conta ativa em nosso banco."},
    {{OPEN_ACCONT, Status::NOT_FOUND},        "🚫 Não foi possível criar sua conta: Banco não encontrado."},


    // --- INFO_BANK ---
    {{INFO_BANK, Status::SUCCESS},            "📄Infomações do Banco"},
    {{INFO_BANK, Status::NOT_FOUND},          "🚫Banco não encontrado"},


    // --- INFO_ACCOUNT ---
    {{INFO_ACCOUNT, Status::SUCCESS},        "📄Infomações da Conta"},
    {{INFO_ACCOUNT, Status::NOT_FOUND},      "🚫Banco ou Conta não encontrado"},

    // --- CHECK_BALANCE ---
    {{CHECK_BALANCE, Status::SUCCESS},        "💰 Extrato gerado com sucesso. Confira seus valores abaixo."},
    {{CHECK_BALANCE, Status::NOT_FOUND},      "🚫 Você ainda não possui uma conta. Use 'Abrir Conta' primeiro."},

    // --- NEW_COIN ---
    {{NEW_MONEY, Status::SUCCESS},             "🪙 Uma nova moeda foi registrada na economia do servidor."},
    {{NEW_MONEY, Status::ALREADY_EXIST},       "⚠️ Essa moeda já existe ou possui um símbolo duplicado."},
    {{NEW_MONEY, Status::NOT_FOUND},           "❌ Erro: Autoridade bancária não encontrada para criar moedas."},

    {{INFO_MONEY, Status::SUCCESS},             "🪙 Informação da Moeda"},
    {{INFO_MONEY, Status::NOT_FOUND},           "🚫 Moeda não encontrada ou o Banco nâo foi aberto neste servidor"},


    // --- PAYMENT ---
    {{PAYMENT, Status::SUCCESS},              "💸 Pagamento processado! O destinatário já recebeu os fundos."},
    {{PAYMENT, Status::NOT_ENOUGH_BALANCE},   "📉 Saldo insuficiente para realizar este pagamento."},
    {{PAYMENT, Status::NOT_FOUND},            "👤 Destinatário não encontrado no sistema ou o banco nâo existe."},

    // --- DEPOSIT ---
    {{DEPOSIT, Status::SUCCESS},              "📥 Depósito confirmado! O valor foi adicionado ao seu saldo seguro."},
    {{DEPOSIT, Status::NOT_ENOUGH_BALANCE},   "❌ Você não possui essa quantia em mãos para depositar."},
    {{DEPOSIT, Status::NOT_FOUND},            "🚫 Conta de destino inexistente ou o banco nâo existe."},

    // --- TRANSFERENCE ---
    {{TRANSFERENCE, Status::SUCCESS},         "📲 Transferência realizada com sucesso entre contas."},
    {{TRANSFERENCE, Status::NOT_ENOUGH_BALANCE},"⚠️ Saldo insuficiente para completar a transferência."},
    {{TRANSFERENCE, Status::NOT_FOUND},       "🔍 Uma das contas envolvidas na transação não foi localizada."}
};
