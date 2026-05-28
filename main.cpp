#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <dpp/appcommand.h>
#include <dpp/dispatcher.h>
#include <dpp/dpp.h>
#include <dpp/intents.h>
#include <dpp/message.h>
#include <dpp/once.h>
#include <dpp/snowflake.h>
#include "bot_sys.hpp"
#include "formater.hpp"
#include "template_PT.hpp"
#include <ctime>
#define SAVE_BREAK 1800


static DiogoBotSys sys;
static std::time_t last_saved = 0;


int main() {
    std::string token = getenv("BOT_TOKEN");
    /* Setup the bot */
    dpp::cluster bot(token, dpp::i_default_intents | dpp::i_message_content);

    bot.on_log(dpp::utility::cout_logger());

    /* The event is fired when someone issues your commands */
    bot.on_slashcommand([](const dpp::slashcommand_t& event) {
        if(event.command.get_command_name() == CMD_OPEN_BANK) {
            event.reply(
                payloadAssembly(
                    sys.open_bank(event.command.guild_id.str())
                )
            );
        }
        else if(event.command.get_command_name() == CMD_INIT_USER) {
            event.reply(
                payloadAssembly(
                    sys.init_user(event.command.guild_id.str(), event.command.usr.id.str(),
                        std::get<std::string>(event.get_parameter(ARG_USER_NAME))
                    )
                )
            );
        }
        else if(event.command.get_command_name() == CMD_INFO_BANK) {
            event.reply(
                payloadAssembly(
                    sys.bank_info(event.command.guild_id.str())
                )
            );
        }
        else if(event.command.get_command_name() == CMD_INFO_ACCOUNT) {
            event.reply(
                payloadAssembly(
                    sys.user_info(event.command.guild_id.str(), event.command.usr.id.str())
                )
            );
        }
        else if(event.command.get_command_name() == CMD_NEW_MONEY) {
            event.reply(
                payloadAssembly(
                    sys.money_new(event.command.guild_id.str(),
                        std::get<std::string>(event.get_parameter(ARG_MONEY_ID)),
                        std::get<std::string>(event.get_parameter(ARG_MONEY_SYMBOL))
                    )
                )
            );
        }
        else if(event.command.get_command_name() == CMD_INFO_MONEY) {
            event.reply(
                payloadAssembly(
                    sys.money_info(event.command.guild_id.str(),
                        std::get<std::string>(event.get_parameter(ARG_MONEY_ID))
                    )
                )
            );
        }
        else if(event.command.get_command_name() == CMD_DEPOSIT) {
            int64_t value = std::get<int64_t>(event.get_parameter(ARG_MONEY_VALUE));
            if (value < 1) {
                event.reply(dpp::message("O Valor deve ser positivo").set_flags(dpp::m_ephemeral));
                return;
            }

            event.reply(
                payloadAssembly(
                    sys.deposit(event.command.guild_id.str(),
                        std::get<dpp::snowflake>(event.get_parameter(ARG_RECEIVER_ID)).str(),                        std::get<std::string>(event.get_parameter("id-da-moeda")),
                        value
                    )
                )
            );
        }
        else if(event.command.get_command_name() == CMD_PAYMENT) {
            int64_t value = std::get<int64_t>(event.get_parameter(ARG_MONEY_VALUE));
            if (value < 1) {
                event.reply(dpp::message("O Valor deve ser positivo").set_flags(dpp::m_ephemeral));
                return;
            }
            event.reply(
                payloadAssembly(
                    sys.pay(event.command.guild_id.str(),
                        value,
                        std::get<std::string>(event.get_parameter(ARG_MONEY_ID)),
                        event.command.usr.id.str()
                    )
                )
            );
        }
        else if(event.command.get_command_name() == CMD_TRANSFERENCE) {
            int64_t value = std::get<int64_t>(event.get_parameter(ARG_MONEY_VALUE));
            if (value < 1) {
                event.reply(dpp::message("O Valor deve ser positivo").set_flags(dpp::m_ephemeral));
                return;
            }
            event.reply(
                payloadAssembly(
                    sys.transference(event.command.guild_id.str(),
                        value,
                        std::get<std::string>(event.get_parameter(ARG_MONEY_ID)),
                        event.command.usr.id.str(),
                        std::get<dpp::snowflake>(event.get_parameter(ARG_RECEIVER_ID)).str()
                    )
                )
            );
        }
        else {
            event.reply("Erro ao executar o comando, talvez ele não exista ou seja um fantasma");
        }

        if(last_saved == 0 || std::difftime(std::time(NULL), last_saved) > SAVE_BREAK) {
           // db.save();
           // std::cout << "Saved in " << db.data_file_name << "\n";
            last_saved = std::time(NULL);
        }
    });

    bot.on_ready([&bot](const dpp::ready_t& event) {

        if (dpp::run_once<struct register_bot_commands>()) {
            //bot.global_bulk_command_delete();
            bot.global_command_create(dpp::slashcommand(CMD_OPEN_BANK, CMD_OPEN_BANK_DESCRIPTION, bot.me.id));
            bot.global_command_create(dpp::slashcommand(CMD_INIT_USER, CMD_INIT_USER_DESCRIPTION, bot.me.id)
                .add_option(dpp::command_option(dpp::co_string, ARG_USER_NAME, ARG_USER_NAME_DESCRIPTION, true))
            );
            bot.global_command_create(dpp::slashcommand(CMD_INFO_BANK, CMD_INFO_BANK_DESCRIPTION, bot.me.id));
            bot.global_command_create(dpp::slashcommand(CMD_INFO_ACCOUNT, CMD_INFO_ACCOUNT_DESCRIPTION, bot.me.id));
            bot.global_command_create(dpp::slashcommand(CMD_NEW_MONEY, CMD_NEW_MONEY_DESCRIPTION, bot.me.id)
                .add_option(dpp::command_option(dpp::co_string, ARG_MONEY_ID, ARG_MONEY_ID_DESCRIPTION, true))
                .add_option(dpp::command_option(dpp::co_string, ARG_MONEY_SYMBOL, ARG_MONEY_SYMBOL_DESCRIPTION, true))
            );
            bot.global_command_create(dpp::slashcommand(CMD_INFO_MONEY, CMD_INFO_MONEY_DESCRIPTION, bot.me.id)
                .add_option(dpp::command_option(dpp::co_string, ARG_MONEY_ID, ARG_MONEY_ID_DESCRIPTION, true))
            );
            bot.global_command_create(dpp::slashcommand(CMD_DEPOSIT, CMD_DEPOSIT_DESCRIPTION, bot.me.id)
                .add_option(dpp::command_option(dpp::co_user, ARG_RECEIVER_ID, ARG_RECEIVER_ID_DESCRIPTION, true))
                .add_option(dpp::command_option(dpp::co_string, ARG_MONEY_ID, ARG_MONEY_ID_DESCRIPTION, true))
                .add_option(dpp::command_option(dpp::co_integer, ARG_MONEY_VALUE, ARG_MONEY_VALUE_DESCRIPTION, true))
            );
            bot.global_command_create(dpp::slashcommand(CMD_PAYMENT, CMD_PAYMENT_DESCRIPTION, bot.me.id)
                .add_option(dpp::command_option(dpp::co_string, ARG_MONEY_ID, ARG_MONEY_ID_DESCRIPTION, true))
                .add_option(dpp::command_option(dpp::co_integer, ARG_MONEY_VALUE, ARG_MONEY_VALUE_DESCRIPTION, true))
            );
            bot.global_command_create(dpp::slashcommand(CMD_TRANSFERENCE, CMD_TRANSFERENCE_DESCRIPTION, bot.me.id)
                .add_option(dpp::command_option(dpp::co_user, ARG_RECEIVER_ID, ARG_RECEIVER_ID_DESCRIPTION, true))
                .add_option(dpp::command_option(dpp::co_string, ARG_MONEY_ID, ARG_MONEY_ID_DESCRIPTION, true))
                .add_option(dpp::command_option(dpp::co_integer, ARG_MONEY_VALUE, ARG_MONEY_VALUE_DESCRIPTION, true))
            );
        }
    });

    bot.start(dpp::st_wait);

    return 0;
}
