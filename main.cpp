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
#include "central_bank.hpp"
#include "interface.hpp"
#include <ctime>
#include <sstream>
#define SAVE_BREAK 1800


static CentralBank db("bank.bin");
static std::time_t last_saved = 0;


std::string formatMention(dpp::snowflake* id, size_t qnt) {
    std::stringstream buffer;
    for(int i = 0; i < qnt; i++) {
        buffer << "<@" << id->str() << "> ";
    }
    return buffer.str();
}


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
        else if(event.command.get_command_name() == "depositar") {
            int64_t value = std::get<int64_t>(event.get_parameter("valor"));
            if (value < 1) {
                event.reply(dpp::message("O Valor deve ser positivo").set_flags(dpp::m_ephemeral));
                return;
            }

            event.reply(
                payloadAssembly(
                    cmd::deposit(&db, event.command.guild_id.str(),
                        std::get<dpp::snowflake>(event.get_parameter("id-destinatario")).str(),                        std::get<std::string>(event.get_parameter("id-da-moeda")),
                        value
                    )
                )
            );
        }
        else if(event.command.get_command_name() == "sacar") {
            int64_t value = std::get<int64_t>(event.get_parameter("valor"));
            if (value < 1) {
                event.reply(dpp::message("O Valor deve ser positivo").set_flags(dpp::m_ephemeral));
                return;
            }
            event.reply(
                payloadAssembly(
                    cmd::pay(&db, event.command.guild_id.str(),
                        value,
                        std::get<std::string>(event.get_parameter("id-da-moeda")),
                        event.command.usr.id.str()
                    )
                )
            );
        }
        else if(event.command.get_command_name() == "transferir") {
            int64_t value = std::get<int64_t>(event.get_parameter("valor"));
            if (value < 1) {
                event.reply(dpp::message("O Valor deve ser positivo").set_flags(dpp::m_ephemeral));
                return;
            }
            event.reply(
                payloadAssembly(
                    cmd::transference(&db, event.command.guild_id.str(),
                        value,
                        std::get<std::string>(event.get_parameter("id-da-moeda")),
                        event.command.usr.id.str(),
                        std::get<dpp::snowflake>(event.get_parameter("id-destinatario")).str()
                    )
                )
            );
        }
        else {
            event.reply("Erro ao executar o comando, talvez ele não exista ou seja um fantasma");
        }

        if(last_saved == 0 || std::difftime(std::time(NULL), last_saved) > SAVE_BREAK) {
            db.save();
            std::cout << "Saved in " << db.data_file_name << "\n";
            last_saved = std::time(NULL);
        }
    });

    bot.on_ready([&bot](const dpp::ready_t& event) {

        if (dpp::run_once<struct register_bot_commands>()) {
            //bot.global_bulk_command_delete();
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
            bot.global_command_create(dpp::slashcommand("depositar", "Deposita um valor na conta do usuário", bot.me.id)
                .add_option(dpp::command_option(dpp::co_user, "id-destinatario", "identificador de quem vai receber", true))
                .add_option(dpp::command_option(dpp::co_string, "id-da-moeda", "O nome ou Identificador", true))
                .add_option(dpp::command_option(dpp::co_integer, "valor", "valor da transação", true))
            );
            bot.global_command_create(dpp::slashcommand("sacar", "Saca um valor", bot.me.id)
                .add_option(dpp::command_option(dpp::co_string, "id-da-moeda", "O nome ou Identificador", true))
                .add_option(dpp::command_option(dpp::co_integer, "valor", "valor da transação", true))
            );
            bot.global_command_create(dpp::slashcommand("transferir", "Trasfere um valor para um usuário", bot.me.id)
                .add_option(dpp::command_option(dpp::co_user, "id-destinatario", "identificador de quem vai receber", true))
                .add_option(dpp::command_option(dpp::co_string, "id-da-moeda", "O nome ou Identificador", true))
                .add_option(dpp::command_option(dpp::co_integer, "valor", "valor da transação", true))
            );
        }
    });

    bot.start(dpp::st_wait);

    return 0;
}
