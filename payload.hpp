#include <string>
#include <cstdint>
typedef uint32_t cents;


struct MoneyType {
    std::string id;
    std::string symbol;
};

struct Money {
    MoneyType _mt;
    cents value;
};


namespace payload
{

    struct Deposit {
        cents value;
        MoneyType mt_;
        std::string to_id;
    };


    struct Trasference {
        cents value;
        MoneyType mt_;
        std::string to_id;
        std::string from_id;
    };

    struct Pay {
        cents value;
        MoneyType mt_;
        std::string from_id;
    };

};
