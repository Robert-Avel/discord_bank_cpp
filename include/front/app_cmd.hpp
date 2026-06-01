#pragma once

#include "bot_sys.hpp"
#include <dpp/dispatcher.h>


namespace cmd {
    void open_bank(const dpp::slashcommand_t& event, DiogoBotSys& bot);
    void init_user(const dpp::slashcommand_t& event, DiogoBotSys& bot);
    void bank_info(const dpp::slashcommand_t& event, DiogoBotSys& bot);
    void user_info(const dpp::slashcommand_t& event, DiogoBotSys& bot);
    void money_new(const dpp::slashcommand_t& event, DiogoBotSys& bot);
    void money_info(const dpp::slashcommand_t& event, DiogoBotSys& bot);
    void deposit(const dpp::slashcommand_t& event, DiogoBotSys& bot);
    void pay(const dpp::slashcommand_t& event, DiogoBotSys& bot);
    void transference(const dpp::slashcommand_t& event, DiogoBotSys& bot);
    void hire_user(const dpp::slashcommand_t& event, DiogoBotSys& bot);
    void fire_user(const dpp::slashcommand_t& event, DiogoBotSys& bot);
    void pay_client(const dpp::slashcommand_t& event, DiogoBotSys& bot);
}
