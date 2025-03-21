#include "SIM7080G_TCP.hpp"
#include "SIM7080G_SERIAL.hpp"
#include <fstream>
#include <nlohmann/json.hpp>
using json = nlohmann::json;

void send_TCP_packet_data(json *j) {
    std::vector<std::uint8_t> v_cbor = json::to_cbor(*j);

    String command = "AT+CASEND=0," + (String)(v_cbor.size());
    String response = send_AT(command);

    if (response.indexOf(">") != -1) {
        send_AT((const char *)v_cbor.data(), v_cbor.size());
    }
    send_AT("AT+CACLOSE=0");
}

void TCP_send()
{
    json j = {
        {"imei", send_AT("AT+GSN")},
    };
    send_AT("AT+CAOPEN=0,0,\"TCP\",\"rnthv-185-223-151-250.a.free.pinggy.link\",46205");
    send_TCP_packet_data(&j);


    //cf datasheet
    //attendre le charactère '>' avant d'envoyer la data
    /*String toto = send_AT("AT+CASEND=0,6");
    if (toto.indexOf(">") != -1) {
        send_AT("coucou");
    }*/


    //send_TCP_packet_data(&j);
    //send_AT(AT+CARECV,1460);
}