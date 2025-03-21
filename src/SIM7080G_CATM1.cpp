#include "SIM7080G_CATM1.hpp"

bool handle_pdp() {
    unsigned long startTime = millis();
    unsigned long timeout = 10000;
    String command = "";

    while (millis() - startTime < timeout) {
        command = send_AT("AT+CNACT=0,1", 10000);
        if (command.indexOf("0,ACTIVE") != -1) {
            return true;
        }
        delay(100);
    }
    return false;
}

bool handle_cereg() {
    unsigned long startTime = millis();
    unsigned long timeout = 240000;
    String command = "";

    while (millis() - startTime < timeout) {
        command = send_AT("AT+CEREG?");
        if (command.indexOf("+CEREG: 0,5") != -1) {
            return true;
        }
        if (command.indexOf("+CEREG: 0,3") != -1) {
            return false;
        }
        if (command.indexOf("+CEREG: 0,0") != -1) {
            return false;
        }
        delay(100);
    }
    return false;
}

void handle_ip() {
    String command = send_AT("AT+CNACT?");
    int start_index = command.indexOf('"');

    while (start_index != -1) {
        int end_index = command.indexOf('"', start_index + 1);
        if (end_index != -1) {
            String ip_address = command.substring(start_index + 1, end_index);
            if (ip_address != "0.0.0.0") {
                Serial.print("Valid IP Address found: ");
                Serial.println(ip_address);
            }
        }
        start_index = command.indexOf('"', end_index + 1);
    }
}

void setup_CATM1()
{
    //You must turn off GNSS before turning on CATM1
    Serial.println(send_AT("AT+CNMP=38"));

    /* WARNING on the ARGALI SIM C3 V1.0 the SIMCOM processor used is
    SIM7080G-M that does not feature NB-IOT.
    1 -> CAT-M1 et 2 -> NB-IOT */

    Serial.println(send_AT("AT+CMNB=1"));

    //APP Network Deactive(PDP context)
    Serial.println(send_AT("AT+CNACT=0,0"));

    //Paramétrage de l'APN (Access Point Name)
    Serial.println(send_AT("AT+CGDCONT=1,\"IP\",\"iot.1nce.net\""));
    Serial.println(send_AT("AT+CGNAPN"));
    Serial.println(send_AT("AT+CNCFG=0,1,iot.1nce.net"));

    //APP Network Active (PDP context)
    if (handle_pdp() == false) {
        Serial.println("PDP not ready");
    } else {
        Serial.println("PDP ready !");
    }

    //We wait for the SIM7080G to register to the local 4G antenna
    if (handle_cereg() == false) {
        Serial.println("CEREG not ready");
    } else {
        Serial.println("CEREG ready !");
    }

    // Vérifier si l'IP est existante
    handle_ip();

    //Informations for you on CAT-M1 connexion
    Serial.println(send_AT("AT+CGATT?"));
    Serial.println(send_AT("AT+GSN"));
    Serial.println(send_AT("AT+CCID"));
    Serial.println(send_AT("AT+COPS?"));
    Serial.println(send_AT("AT+CEREG?"));
    // Signal Quality
    Serial.println(send_AT("AT+CSQ"));
}

void loop_CATM1()
{
    Serial.println(send_AT("AT+CEREG?"));
    Serial.println(send_AT("AT+CSQ"));
}
