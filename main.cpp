#include <cstdlib>
#include <dpp/dispatcher.h>
#include <dpp/dpp.h>
#include <dpp/intents.h>
#include <dpp/message.h>
#include <dpp/once.h>
#include "bank.cpp"
#include "payload.hpp"
#include "interface.cpp"

static CentralBank db;


dpp::embed payloadAssembly(const PayLoad& pl) {
    return dpp::embed()
        .set_title(pl.operation)
        .set_description(pl.message)
    ;
}


int main() {
    std::string token = getenv("BOT_TOKEN");
    /* Setup the bot */
    dpp::cluster bot(token, dpp::i_default_intents | dpp::i_message_content);

    bot.on_log(dpp::utility::cout_logger());

    /* The event is fired when someone issues your commands */
    bot.on_slashcommand([&bot](const dpp::slashcommand_t& event) {
        if(event.command.get_command_name() == "open-bank") {
            event.reply(
                payloadAssembly(
                    cmd::openbank(&db, event.command.guild_id.str())                )
            );
        }
        else if(event.command.get_command_name() == "open-accont") {
            event.reply(
                payloadAssembly(
                    cmd::openaccont(&db, event.command.guild_id.str(), event.command.usr.id.str())
                )
            );
        }
        else {
            event.reply("Erro ao executar o comando, talvez ele não exista ou seja um fantasma");
        }
    });

    bot.on_ready([&bot](const dpp::ready_t& event) {

        if (dpp::run_once<struct register_bot_commands>()) {
            /* Create and register a command when the bot is ready */
            bot.global_command_create(dpp::slashcommand("open-bank", "Open a New bank in this server", bot.me.id));
            bot.global_command_create(dpp::slashcommand("open-accont", "Open a New accont for a user in this server", bot.me.id));
            bot.global_command_create(dpp::slashcommand("bankinfo", "Server Bank Info", bot.me.id));
        }
    });

    bot.start(dpp::st_wait);

    return 0;
}
