#include <cstdlib>
#include <dpp/dispatcher.h>
#include <dpp/dpp.h>
#include <dpp/intents.h>
#include <dpp/message.h>
#include <dpp/once.h>
#include "bank.cpp"
#include "simple_format.cpp"

static CentralBank db;

int main() {
    std::string token = getenv("BOT_TOKEN");
    /* Setup the bot */
    dpp::cluster bot(token, dpp::i_default_intents | dpp::i_message_content);

    bot.on_log(dpp::utility::cout_logger());

    /* The event is fired when someone issues your commands */
    bot.on_slashcommand([&bot](const dpp::slashcommand_t& event) {
        /* Check which command they ran */
        if(event.command.get_command_name() == "openbank") {
            db.openBank(event.command.guild_id.str());
            event.reply("A New Bank was created for this server");
        }
    });

    bot.on_ready([&bot](const dpp::ready_t& event) {

        if (dpp::run_once<struct register_bot_commands>()) {
            /* Create and register a command when the bot is ready */
            bot.global_command_create(dpp::slashcommand("openbank", "Open a New bank in this server", bot.me.id));
            bot.global_command_create(dpp::slashcommand("bankinfo", "Server Bank Info", bot.me.id));
        }
    });

    bot.start(dpp::st_wait);

    return 0;
}
