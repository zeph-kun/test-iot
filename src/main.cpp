#include <Arduino.h>
#include "SIM7080G_SERIAL.hpp"
#include "ARGALI_PINOUT.hpp"
#include "SIM7080G_POWER.hpp"
#include "SIM7080G_GNSS.hpp"
#include "SIM7080G_CATM1.hpp"
#include "SIM7080G_TCP.hpp"

// Serial = port du PC

unsigned long period1;

void everyXs() {
  if ((millis() - period1) > 1000) {
    period1 = millis();
    //loop_CATM1();
    parse_GNSS_data(send_AT("AT+CGNSINF"));
  }
}

void setup() {
  pinMode(PIN_PWRKEY, OUTPUT); // Déclaration de la pin powerkey du cpu en sortie
  turn_on_SIM7080G();
  Serial.begin(115200); //9600
  Sim7080G.begin(Sim7080G_BAUDRATE, SERIAL_8N1, 20, 21);
  period1 = millis();

  setup_CATM1();
  Serial.println("Setup CatM1 done");
  TCP_send();
  Serial.println("Data send");
}

void loop() {
  //everyXs();
}

/*void battery_SIM7080() {
  String tmp = send_AT("AT+CBC");
  tmp = tmp.substring(20, 25);
  if (tmp.charAt(0) == ',') {
    tmp.remove(0, 1);
  }
  return tmp;
}*/