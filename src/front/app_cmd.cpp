#include "app_cmd.hpp"
#include "base_payload.hpp"
#include "formater.hpp"
#include "template_PT.hpp"
#include <dpp/snowflake.h>
#include <string>


inline static void eventReply(const dpp::slashcommand_t& event, BasePayLoad pl) {
    event.reply(
        payloadAssembly(
            pl
        )
    );
}


void cmd::open_bank(const dpp::slashcommand_t& event, DiogoBotSys& bot) {
    eventReply( event, bot.open_bank(event.command.guild_id.str())
    );
}

void cmd::init_user(const dpp::slashcommand_t& event, DiogoBotSys& bot) {
    eventReply(
        event,
        bot.init_user(
            event.command.guild_id.str(),
            event.command.usr.id.str(),
            std::get<std::string>(event.get_parameter(ARG_USER_NAME)
            )
        )
    );
}

void cmd::bank_info(const dpp::slashcommand_t& event, DiogoBotSys& bot) {
    eventReply(
        event,
        bot.bank_info(event.command.guild_id.str())
    );
}

void cmd::user_info(const dpp::slashcommand_t& event, DiogoBotSys& bot) {
    eventReply(
        event,
        bot.user_info(
            event.command.guild_id.str(),
            event.command.usr.id.str()
        )
    );
}


void cmd::money_new(const dpp::slashcommand_t& event, DiogoBotSys& bot) {
    eventReply(
        event,
        bot.money_new(event.command.guild_id.str(),
            std::get<std::string>(event.get_parameter(ARG_MONEY_ID)),
            std::get<std::string>(event.get_parameter(ARG_MONEY_SYMBOL))
        )
    );
}

void cmd::money_info(const dpp::slashcommand_t& event, DiogoBotSys& bot) {
    eventReply(
        event,
        bot.money_info(event.command.guild_id.str(),
            std::get<std::string>(event.get_parameter(ARG_MONEY_ID))
        )
    );
}

void cmd::deposit(const dpp::slashcommand_t& event, DiogoBotSys& bot) {
    int64_t value = std::get<int64_t>(event.get_parameter(ARG_MONEY_VALUE));
    if (value < 1) {
        event.reply(dpp::message("O Valor deve ser positivo").set_flags(dpp::m_ephemeral));
        return;
    }

    eventReply(
        event,
        bot.deposit(event.command.guild_id.str(),
            std::get<dpp::snowflake>(event.get_parameter(ARG_RECEIVER_ID)).str(),
            std::get<std::string>(event.get_parameter(ARG_MONEY_ID)),
            value
        )
    );
}

void cmd::pay(const dpp::slashcommand_t& event, DiogoBotSys& bot) {
    int64_t value = std::get<int64_t>(event.get_parameter(ARG_MONEY_VALUE));
    if (value < 1) {
        event.reply(dpp::message("O Valor deve ser positivo").set_flags(dpp::m_ephemeral));
        return;
    }
    eventReply(
        event,
        bot.pay(event.command.guild_id.str(),
            value,
            std::get<std::string>(event.get_parameter(ARG_MONEY_ID)),
            event.command.usr.id.str()
        )
    );
}

void cmd::transference(const dpp::slashcommand_t& event, DiogoBotSys& bot) {
    int64_t value = std::get<int64_t>(event.get_parameter(ARG_MONEY_VALUE));
    if (value < 1) {
        event.reply(dpp::message("O Valor deve ser positivo").set_flags(dpp::m_ephemeral));
        return;
    }

    eventReply(
        event,
        bot.transference(event.command.guild_id.str(),
            value,
            std::get<std::string>(event.get_parameter(ARG_MONEY_ID)),
            event.command.usr.id.str(),
            std::get<dpp::snowflake>(event.get_parameter(ARG_RECEIVER_ID)).str()
        )
    );
}

void cmd::hire_user(const dpp::slashcommand_t& event, DiogoBotSys& bot) {
    int64_t value = std::get<int64_t>(event.get_parameter(ARG_MONEY_VALUE));
    if (value < 1) {
        event.reply(dpp::message("O Valor deve ser positivo").set_flags(dpp::m_ephemeral));
        return;
    }

    eventReply(
        event,
        bot.hire_user(
            event.command.guild_id.str(),
            std::get<dpp::snowflake>(event.get_parameter(ARG_USER_NAME)).str(),
            std::get<std::string>(event.get_parameter(ARG_JOB_NAME)),
            std::get<std::string>(event.get_parameter(ARG_MONEY_ID)),
            value
        )
    );
}

void cmd::fire_user(const dpp::slashcommand_t& event, DiogoBotSys& bot) {
    eventReply(
        event,
        bot.fire_user(
            event.command.guild_id.str(),
            std::get<dpp::snowflake>(event.get_parameter(ARG_USER_NAME)).str()
        )
    );
}

void cmd::pay_client(const dpp::slashcommand_t& event, DiogoBotSys& bot) {
    eventReply(
        event,
        bot.pay_client(
            event.command.guild_id.str(),
            event.command.usr.id.str()
        )
    );
}
