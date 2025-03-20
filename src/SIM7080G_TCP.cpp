#include "SIM7080G_TCP.hpp"
#include "SIM7080G_SERIAL.hpp"

void TCP_send()
{
    
    send_AT("AT+CAOPEN=0,0,\"TCP\",\"rnkuy-2a04-cec0-115b-37ed-392d-81be-5e94-59f4.a.free.pinggy.link\",36585");
    
    //cf datasheet
    send_AT("AT+CASEND=0,6");
    //attendre le charactère '>' avant d'envoyer la data
    send_AT("coucou");

    //send_TCP_packet_data(&j);

    send_AT("AT+CACLOSE=0");
    //send_AT(AT+CARECV,1460);

}