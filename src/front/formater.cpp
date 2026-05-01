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
        return FieldMap{
            {fields_PT.at(PL_TEXT)[0], string}
        };
    }
    else if (std::holds_alternative<MoneyType>(pl)) {
        auto mt = std::get<MoneyType>(pl);
        return FieldMap {
            {fields_PT.at(PL_MONEY_TYPE)[0], mt.id},
            {fields_PT.at(PL_MONEY_TYPE)[1], mt.symbol}
        };
    }
    else if (std::holds_alternative<Money>(pl)) {
        auto m = std::get<Money>(pl);
        return FieldMap{
            {fields_PT.at(PL_MONEY)[0], m.format()}
        };
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
            {fields_PT.at(PL_DEPOSIT)[0], d.mt_.id},
            {fields_PT.at(PL_DEPOSIT)[1], std::to_string(d.value)},
            {fields_PT.at(PL_DEPOSIT)[2], d.to_id}
        };
    }
    else if (std::holds_alternative<payload::Pay>(pl)) {
        auto p = std::get<payload::Pay>(pl);
        return FieldMap{
            {fields_PT.at(PL_PAY)[0], p.mt_.id},
            {fields_PT.at(PL_PAY)[1], std::to_string(p.value)},
            {fields_PT.at(PL_PAY)[2], p.from_id}
        };
    }
    else if (std::holds_alternative<payload::Trasference>(pl)) {
        auto p = std::get<payload::Trasference>(pl);
        return FieldMap{
            {fields_PT.at(PL_TRANSFERENCE)[0], p.mt_.id},
            {fields_PT.at(PL_TRANSFERENCE)[1], std::to_string(p.value)},
            {fields_PT.at(PL_TRANSFERENCE)[2], p.from_id},
            {fields_PT.at(PL_TRANSFERENCE)[3], p.to_id}
        };
    }
    else if (std::holds_alternative<payload::Bank>(pl)) {
        auto p = std::get<payload::Bank>(pl);
        return FieldMap{
            {fields_PT.at(PL_BANK)[0], p.id},
            {fields_PT.at(PL_BANK)[1], std::to_string(p.accountN)}
        };
    }
    else if (std::holds_alternative<payload::Account>(pl)) {
        auto p = std::get<payload::Account>(pl);
        return FieldMap{
            {fields_PT.at(PL_ACCOUNT)[0], p.id},
            {fields_PT.at(PL_ACCOUNT)[1], p.balances}
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
