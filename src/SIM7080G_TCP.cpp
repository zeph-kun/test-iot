#include "SIM7080G_TCP.hpp"
#include "SIM7080G_SERIAL.hpp"
/*#include <fstream>
#include <nlohmann/json.hpp>
using json = nlohmann::json;
using namespace nlohmann::literals;*/

void TCP_send()
{
    send_AT("AT+CAOPEN=0,0,\"TCP\",\"rnsgp-2a04-cec0-115b-37ed-392d-81be-5e94-59f4.a.free.pinggy.link\",33777");
    /*json j = R"({"compact": true, "schema": 0})"_json;
    std::vector<std::uint8_t> v_cbor = json::to_cbor(j);*/


    //cf datasheet
    //attendre le charactère '>' avant d'envoyer la data
    String toto = send_AT("AT+CASEND=0,6");
    if (toto.indexOf(">") != -1) {
        send_AT("coucou");
    }


    //send_TCP_packet_data(&j);

    send_AT("AT+CACLOSE=0");
    //send_AT(AT+CARECV,1460);
}