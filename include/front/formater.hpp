#pragma once
#include "base_payload.hpp"
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
