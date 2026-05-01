#include <cstdlib>
#include <dpp/appcommand.h>
#include <dpp/dispatcher.h>
#include <dpp/dpp.h>
#include <dpp/intents.h>
#include <dpp/message.h>
#include <dpp/once.h>
#include "sysbank.hpp"
#include "interface.hpp"

static CentralBank db;

dpp::embed payloadAssembly(const FinalPayLoad& pl) {
    dpp::embed buffer;
    buffer.set_title(pl.operation)
          .set_description(pl.message);

    for(const auto& [name, value]: pl.fields) {
        buffer.add_field(name, value, false);
    }

    return buffer;
}


int main() {
    std::string token = getenv("BOT_TOKEN");
    /* Setup the bot */
    dpp::cluster bot(token, dpp::i_default_intents | dpp::i_message_content);

    bot.on_log(dpp::utility::cout_logger());

    /* The event is fired when someone issues your commands */
    bot.on_slashcommand([](const dpp::slashcommand_t& event) {
        if(event.command.get_command_name() == "abrir-banco") {
            event.reply(
                payloadAssembly(
                    cmd::open_bank(&db, event.command.guild_id.str())
                )
            );
        }
        else if(event.command.get_command_name() == "abrir-conta") {
            event.reply(
                payloadAssembly(
                    cmd::open_accont(&db, event.command.guild_id.str(), event.command.usr.id.str())
                )
            );
        }
        else if(event.command.get_command_name() == "ver-banco") {
            event.reply(
                payloadAssembly(
                    cmd::bank_info(&db, event.command.guild_id.str())
                )
            );
        }
        else if(event.command.get_command_name() == "ver-conta") {
            event.reply(
                payloadAssembly(
                    cmd::account_info(&db, event.command.guild_id.str(), event.command.usr.id.str())
                )
            );
        }
        else if(event.command.get_command_name() == "nova-moeda") {
            event.reply(
                payloadAssembly(
                    cmd::money_new(&db, event.command.guild_id.str(),
                        std::get<std::string>(event.get_parameter("id-da-moeda")),
                        std::get<std::string>(event.get_parameter("simbolo-da-moeda"))
                    )
                )
            );
        }
        else if(event.command.get_command_name() == "ver-moeda") {
            event.reply(
                payloadAssembly(
                    cmd::money_info(&db, event.command.guild_id.str(),
                        std::get<std::string>(event.get_parameter("id-da-moeda"))
                    )
                )
            );
        }
        else {
            event.reply("Erro ao executar o comando, talvez ele não exista ou seja um fantasma");
        }
    });

    bot.on_ready([&bot](const dpp::ready_t& event) {


        if (dpp::run_once<struct register_bot_commands>()) {
            //bot.global_bulk_command_delete();
            /* Create and register a command when the bot is ready */
            bot.global_command_create(dpp::slashcommand("abrir-banco", "Abra um novo banco neste servidor.", bot.me.id));
            bot.global_command_create(dpp::slashcommand("abrir-conta", "Abra uma nova conta neste servidor", bot.me.id));
            bot.global_command_create(dpp::slashcommand("ver-banco", "Informações do banco", bot.me.id));
            bot.global_command_create(dpp::slashcommand("ver-conta", "Informações da conta", bot.me.id));
            bot.global_command_create(dpp::slashcommand("nova-moeda", "Adiciona uma nova moeda", bot.me.id)
                .add_option(dpp::command_option(dpp::co_string, "id-da-moeda", "O nome ou Identificador", true))
                .add_option(dpp::command_option(dpp::co_string, "simbolo-da-moeda", "O Simbolo da moeda", true))
            );
            bot.global_command_create(dpp::slashcommand("ver-moeda", "Informações da Moeda", bot.me.id)
                .add_option(dpp::command_option(dpp::co_string, "id-da-moeda", "O nome ou Identificador", true))
            );
        }
    });

    bot.start(dpp::st_wait);

    return 0;
}
