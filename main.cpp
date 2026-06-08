#include <cstddef>
#include <cstdlib>
#include <dpp/appcommand.h>
#include <dpp/dispatcher.h>
#include <dpp/dpp.h>
#include <dpp/intents.h>
#include <dpp/message.h>
#include <dpp/once.h>
#include <dpp/scheduled_event.h>
#include <dpp/snowflake.h>
#include "bot_sys.hpp"
#include "template_PT.hpp"
#include "app_cmd.hpp"
#include <ctime>
#include <iostream>
#include <map>
#include <string>
#include <vector>

#define SAVE_BREAK 1800
typedef void (*Command) (const dpp::slashcommand_t& event, DiogoBotSys& bot);

static DiogoBotSys sys;
static std::time_t last_saved = 0;


std::map<std::string, Command> commands = {
    {CMD_OPEN_BANK, &cmd::open_bank},
    {CMD_INIT_USER, &cmd::init_user},
    {CMD_INFO_BANK, &cmd::bank_info},
    {CMD_INFO_ACCOUNT, &cmd::user_info},
    {CMD_NEW_MONEY, &cmd::money_new},
    {CMD_INFO_MONEY, &cmd::money_info},
    {CMD_DEPOSIT, &cmd::deposit},
    {CMD_PAYMENT, &cmd::pay},
    {CMD_TRANSFERENCE, &cmd::transference},
    {CMD_HIRE_USER, &cmd::hire_user},
    {CMD_FIRE_USER, &cmd::fire_user},
    {CMD_PAY_CLIENT, &cmd::pay_client},
};


int main() {
    std::string token = getenv("BOT_TOKEN");
    /* Setup the bot */
    dpp::cluster bot(token, dpp::i_default_intents | dpp::i_message_content);

    bot.on_log(dpp::utility::cout_logger());


    bot.on_slashcommand([](const dpp::slashcommand_t& event) {
        std::string cmd_name = event.command.get_command_name();

        if (commands.find(cmd_name) == commands.end()) {
            event.reply("Command "+cmd_name+" not found");
        }
        else commands.at(cmd_name)(event, sys);


        if(last_saved == 0 || std::difftime(std::time(NULL), last_saved) > SAVE_BREAK) {
           // db.save();
           // std::cout << "Saved in " << db.data_file_name << "\n";
            last_saved = std::time(NULL);
        }
    });

    bot.on_ready([&bot](const dpp::ready_t& event) {

        if (dpp::run_once<struct register_bot_commands>()) {

            std::vector<dpp::slashcommand> COMMANDS = {
                dpp::slashcommand(CMD_OPEN_BANK, CMD_OPEN_BANK_DESCRIPTION, bot.me.id),

                dpp::slashcommand(CMD_INIT_USER, CMD_INIT_USER_DESCRIPTION, bot.me.id)
                    .add_option(dpp::command_option(dpp::co_string, ARG_USER_NAME, ARG_USER_NAME_DESCRIPTION, true)),

                dpp::slashcommand(CMD_INFO_BANK, CMD_INFO_BANK_DESCRIPTION, bot.me.id),

                dpp::slashcommand(CMD_INFO_ACCOUNT, CMD_INFO_ACCOUNT_DESCRIPTION, bot.me.id)
                    .add_option(dpp::command_option(dpp::co_user, ARG_USER_NAME, ARG_USER_NAME_DESCRIPTION, false)),

                dpp::slashcommand(CMD_NEW_MONEY, CMD_NEW_MONEY_DESCRIPTION, bot.me.id)
                    .add_option(dpp::command_option(dpp::co_string, ARG_MONEY_ID, ARG_MONEY_ID_DESCRIPTION, true))
                    .add_option(dpp::command_option(dpp::co_string, ARG_MONEY_SYMBOL, ARG_MONEY_SYMBOL_DESCRIPTION, true)),

                dpp::slashcommand(CMD_INFO_MONEY, CMD_INFO_MONEY_DESCRIPTION, bot.me.id)
                    .add_option(dpp::command_option(dpp::co_string, ARG_MONEY_ID, ARG_MONEY_ID_DESCRIPTION, true)),

                dpp::slashcommand(CMD_DEPOSIT, CMD_DEPOSIT_DESCRIPTION, bot.me.id)
                    .add_option(dpp::command_option(dpp::co_user, ARG_RECEIVER_ID, ARG_RECEIVER_ID_DESCRIPTION, true))
                    .add_option(dpp::command_option(dpp::co_string, ARG_MONEY_ID, ARG_MONEY_ID_DESCRIPTION, true))
                    .add_option(dpp::command_option(dpp::co_integer, ARG_MONEY_VALUE, ARG_MONEY_VALUE_DESCRIPTION, true)),

                dpp::slashcommand(CMD_PAYMENT, CMD_PAYMENT_DESCRIPTION, bot.me.id)
                    .add_option(dpp::command_option(dpp::co_string, ARG_MONEY_ID, ARG_MONEY_ID_DESCRIPTION, true))
                    .add_option(dpp::command_option(dpp::co_integer, ARG_MONEY_VALUE, ARG_MONEY_VALUE_DESCRIPTION, true)),

                dpp::slashcommand(CMD_TRANSFERENCE, CMD_TRANSFERENCE_DESCRIPTION, bot.me.id)
                    .add_option(dpp::command_option(dpp::co_user, ARG_RECEIVER_ID, ARG_RECEIVER_ID_DESCRIPTION, true))
                    .add_option(dpp::command_option(dpp::co_string, ARG_MONEY_ID, ARG_MONEY_ID_DESCRIPTION, true))
                    .add_option(dpp::command_option(dpp::co_integer, ARG_MONEY_VALUE, ARG_MONEY_VALUE_DESCRIPTION, true)),

                dpp::slashcommand(CMD_HIRE_USER, CMD_HIRE_USER_DESCRIPTION, bot.me.id)
                    .add_option(dpp::command_option(dpp::co_user, ARG_USER_NAME, ARG_USER_NAME_DESCRIPTION, true))
                    .add_option(dpp::command_option(dpp::co_string, ARG_JOB_NAME, ARG_JOB_NAME_DESCRIPTION, true))
                    .add_option(dpp::command_option(dpp::co_string, ARG_MONEY_ID, ARG_MONEY_ID_DESCRIPTION, true))
                    .add_option(dpp::command_option(dpp::co_integer, ARG_MONEY_VALUE, ARG_MONEY_VALUE_DESCRIPTION, true)),

                dpp::slashcommand(CMD_FIRE_USER, CMD_FIRE_USER_DESCRIPTION, bot.me.id)
                    .add_option(dpp::command_option(dpp::co_user, ARG_USER_NAME, ARG_USER_NAME_DESCRIPTION, false)),

                dpp::slashcommand(CMD_PAY_CLIENT, CMD_PAY_CLIENT_DESCRIPTION, bot.me.id)
            };


            #ifdef SERVER_ID
                std::string server_id = SERVER_ID;
                if(server_id.size() <= 1 || server_id.empty()) {
                    exit(-1);
                }
            #endif

            #if defined(DEBUG_MODE)
                std::cout << "Debug Mode..." << "\n";
                bot.guild_bulk_command_create(COMMANDS, std::stoull(server_id));

            #elif defined(RELEASE_MODE)
                std::cout << "Release Mode..." << "\n";
                bot.global_bulk_command_create(COMMANDS);


            #elif defined(CLEAR_MODE)
                std::cout << "Clear Mode..." << "\n";
                bot.global_bulk_command_delete();
                bot.guild_bulk_command_delete(std::stoull(server_id));

            #else
                exit(-1);
            #endif
        }
    });

    bot.start(dpp::st_wait);

    return 0;
}
