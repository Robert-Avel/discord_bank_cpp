#include "base_payload.hpp"
#include <map>

using MsgKey = std::pair<Operation, Status>;

const std::map<Operation, std::string>
operation_PT = {
    {OPEN_BANK, "Abrir Banco"},
    {OPEN_ACCONT, "Abrir Conta"},
    {CHECK_BALANCE, "Saldo de Conta"},
    {NEW_COIN, "Nova Moeda"},
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
    {{OPEN_ACCONT, Status::NOT_FOUND},        "❌ Não foi possível criar sua conta: Banco não encontrado."},

    // --- CHECK_BALANCE ---
    {{CHECK_BALANCE, Status::SUCCESS},        "💰 Extrato gerado com sucesso. Confira seus valores abaixo."},
    {{CHECK_BALANCE, Status::NOT_FOUND},      "🚫 Você ainda não possui uma conta. Use 'Abrir Conta' primeiro."},

    // --- NEW_COIN ---
    {{NEW_COIN, Status::SUCCESS},             "🪙 Uma nova moeda foi registrada na economia do servidor."},
    {{NEW_COIN, Status::ALREADY_EXIST},       "⚠️ Essa moeda já existe ou possui um símbolo duplicado."},
    {{NEW_COIN, Status::NOT_FOUND},           "❌ Erro: Autoridade bancária não encontrada para criar moedas."},

    // --- PAYMENT ---
    {{PAYMENT, Status::SUCCESS},              "💸 Pagamento processado! O destinatário já recebeu os fundos."},
    {{PAYMENT, Status::NOT_ENOUGH_BALANCE},   "📉 Saldo insuficiente para realizar este pagamento."},
    {{PAYMENT, Status::NOT_FOUND},            "👤 Destinatário não encontrado no sistema."},

    // --- DEPOSIT ---
    {{DEPOSIT, Status::SUCCESS},              "📥 Depósito confirmado! O valor foi adicionado ao seu saldo seguro."},
    {{DEPOSIT, Status::NOT_ENOUGH_BALANCE},   "❌ Você não possui essa quantia em mãos para depositar."},
    {{DEPOSIT, Status::NOT_FOUND},            "🚫 Conta de destino inexistente."},

    // --- TRANSFERENCE ---
    {{TRANSFERENCE, Status::SUCCESS},         "📲 Transferência realizada com sucesso entre contas."},
    {{TRANSFERENCE, Status::NOT_ENOUGH_BALANCE},"⚠️ Saldo insuficiente para completar a transferência."},
    {{TRANSFERENCE, Status::NOT_FOUND},       "🔍 Uma das contas envolvidas na transação não foi localizada."}
};
