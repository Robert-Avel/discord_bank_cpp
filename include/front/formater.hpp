#pragma once
#include "base_payload.hpp"
#include <dpp/message.h>
#include <map>
#include <string>
using FieldMap = std::map<std::string, std::string>;


class FinalPayLoad {
    FieldMap formatField(const PayloadVariant& pl);

    public:
    std::string operation;
    std::string status;
    std::string message;
    FieldMap fields;

    FinalPayLoad(const BasePayLoad& bpl);
};



std::string formatMention(dpp::snowflake* id, size_t qnt);

dpp::embed payloadAssembly(const FinalPayLoad& pl);
dpp::embed payloadAssembly(const BasePayLoad& pl);
