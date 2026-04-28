#include "base_payload.hpp"
#include <map>
#include <string>


class FinalPayLoad {
    std::string operation;
    std::string status;
    std::string message;
    std::map<std::string, std::string> fields;

    std::map<std::string, std::string> formatField(PayloadVariant& pl);

    public:
    FinalPayLoad(const BasePayLoad& bpl);
};
