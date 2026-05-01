#include "formater.hpp"
#include "base_payload.hpp"
#include "money.hpp"
#include "template_PT.hpp"
#include <map>
#include <string>
#include <variant>
#include <vector>


FieldMap FinalPayLoad::formatField(const PayloadVariant& pl) {
    if(std::holds_alternative<std::string>(pl)) {
        auto string = std::get<std::string>(pl);
        return FieldMap{{"Obs:", string}};
    }
    else if (std::holds_alternative<MoneyType>(pl)) {
        auto mt = std::get<MoneyType>(pl);
        return FieldMap {{"ID", mt.id}, {"Símbolo", mt.symbol}};
    }
    else if (std::holds_alternative<Money>(pl)) {
        auto m = std::get<Money>(pl);
        return FieldMap{{"Saldo", m.format()}};
    }
    else if (std::holds_alternative<std::vector<Money>>(pl)) {
        auto vm = std::get<std::vector<Money>>(pl);
        FieldMap buffer;
        for(Money m : vm) {
            buffer.insert({m._mt.symbol, std::to_string(m.value)});
        }
        return buffer;
    }
    else if (std::holds_alternative<payload::Deposit>(pl)) {
        auto d = std::get<payload::Deposit>(pl);
        return FieldMap{
            {"Moeda", d.mt_.id},
            {"Valor", std::to_string(d.value)},
            {"Destinatário", d.to_id}
        };
    }
    else if (std::holds_alternative<payload::Pay>(pl)) {
        auto p = std::get<payload::Pay>(pl);
        return FieldMap{
            {"Moeda", p.mt_.id},
            {"Valor", std::to_string(p.value)},
            {"Remetente", p.from_id}
        };
    }
    else if (std::holds_alternative<payload::Trasference>(pl)) {
        auto p = std::get<payload::Trasference>(pl);
        return FieldMap{
            {"Moeda", p.mt_.id},
            {"Valor", std::to_string(p.value)},
            {"Remetente", p.from_id},
            {"Destinatário", p.to_id}
        };
    }
    else if (std::holds_alternative<payload::Bank>(pl)) {
        auto p = std::get<payload::Bank>(pl);
        return FieldMap{
            {"ID", p.id},
            {"Nº Contas", std::to_string(p.accountN)}
        };
    }
    else if (std::holds_alternative<payload::Account>(pl)) {
        auto p = std::get<payload::Account>(pl);
        return FieldMap{
            {"ID", p.id},
            {"Saldo(s)", p.balances}
        };
    }
    else {
        return FieldMap{{"FIELD_ERROR", "PAYLOAD_NOT_FOUND"}};
    }
}

FinalPayLoad::FinalPayLoad(const BasePayLoad& bpl) {
    this->operation = operation_PT.at(bpl.operation);
    this->status = status_PT.at(bpl.status);
    this->message = messages_PT.at({bpl.operation, bpl.status});
    this->fields = formatField(bpl.payload);
}
