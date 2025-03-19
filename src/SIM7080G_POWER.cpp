#include "SIM7080G_POWER.hpp"

void hard_reset() {
    digitalWrite(PIN_PWRKEY, LOW);
    delay(15000);
    digitalWrite(PIN_PWRKEY, OUTPUT_OPEN_DRAIN);
    delay(3000);
}

void turn_on_SIM7080G(){
    digitalWrite(PIN_PWRKEY, LOW);
    delay(200);
    digitalWrite(PIN_PWRKEY, OUTPUT_OPEN_DRAIN);
    delay(3000);
}

void turn_off_SIM7080G() {
    send_AT("AT+CPOWD=1");
}

void reboot() {
    turn_off_SIM7080G();
    turn_on_SIM7080G();
}