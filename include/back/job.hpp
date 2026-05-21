#include <string>
#include "money.hpp"


/* Um Emprego Improvisado, como "fazer um bico por ai" */
class ImprovisedJob {
    std::string global_name;
    Money salary;

    public:
        ImprovisedJob(std::string global_name, cents salary, std::string money_id, std::string money_symbol)
            {ImprovisedJob(global_name, Money{{money_id, money_symbol}, salary});}
        ImprovisedJob(std::string global_name, Money salary):
        global_name(global_name), salary(salary) {}

        std::string getJobName() const {return global_name;}
        Money getSalary() const {return salary;}


        void changeSalary(double porcentage) {
            this->salary.value *= (porcentage / 100);
        }
};


/*Emprego Oficial */
class JobCLT: public ImprovisedJob {
    std::string id;

    public:
        JobCLT(std::string id, std::string global_name, cents salary, std::string money_id, std::string money_symbol):
        ImprovisedJob(global_name, salary, money_id, money_symbol), id(id) {}
};
