#include "formater.hpp"
#include "base_payload.hpp"
#include "money.hpp"
#include "template_PT.hpp"
#include <map>
#include <string>
#include <variant>

template<class... Ts> struct overloaded : Ts... { using Ts::operator()...; };
template<class... Ts> overloaded(Ts...) -> overloaded<Ts...>;

using FieldMap = std::map<std::string, std::string>;

FieldMap FinalPayLoad::formatField(PayloadVariant& pl) {
    return std::visit(overloaded {

        [](std::string& s) {return FieldMap{{"Obs:", s}};},

        [](MoneyType& mt) {return FieldMap {{"ID", mt.id}, {"Símbolo", mt.symbol}};},

        [](Money& m) {return FieldMap{{"Saldo", m.format()}};},

        [](std::vector<Money>& vm) {
            FieldMap buffer;
            for(Money m : vm) {
                buffer.insert({m._mt.symbol, std::to_string(m.value)});
            }
            return buffer;
        },

        [](payload::Deposit& d) {
            return FieldMap{
                {"Moeda", d.mt_.id},
                {"Valor", std::to_string(d.value)},
                {"Destinatário", d.to_id}
            };
        },

        [](payload::Pay& p) {
            return FieldMap{
                {"Moeda", p.mt_.id},
                {"Valor", std::to_string(p.value)},
                {"Remetente", p.from_id}
            };
        },

        [](payload::Trasference& p) {
            return FieldMap{
                {"Moeda", p.mt_.id},
                {"Valor", std::to_string(p.value)},
                {"Remetente", p.from_id},
                {"Destinatário", p.to_id}
            };
        },
        [](auto& a) {return FieldMap{{"FIELD_ERROR", "PAYLOAD_NOT_FOUND"}};}
    }, pl);
}


FinalPayLoad::FinalPayLoad(const BasePayLoad& bpl) {
    this->operation = operation_PT.at(bpl.operation);
    this->status = status_PT.at(bpl.status);
    this->message = messages_PT.at({bpl.operation, bpl.status});


}
