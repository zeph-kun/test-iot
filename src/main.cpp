#include <Arduino.h>
#include "SIM7080G_SERIAL.hpp"
#include "ARGALI_PINOUT.hpp"

// Serial = port du PC

/*
#define PIN_PWRKEY 7
#define Sim7080G Serial1
#define Sim7080G_BAUDRATE 57600
*/

unsigned long period1;

void turn_on_SIM7080G(){
  digitalWrite(PIN_PWRKEY, LOW);
  delay(200);
  digitalWrite(PIN_PWRKEY, OUTPUT_OPEN_DRAIN);
  delay(3000);
}

void everyXs() {
  if ((millis() - period1) > 3000) {
    period1 = millis();
  }
}

void turn_off_SIM7080G() {

}

void setup_GNSS() {

}

void loop_GNSS() {

}

void battery_SIM7080() {
  String tmp = send_AT("AT+CBC");
  tmp = tmp.substring(20, 25);
  if (tmp.charAt(0) == ',') {
    tmp.remove();
  }
}

void setup() {
  pinMode(PIN_PWRKEY, OUTPUT); // déclaration de la pin powerkey du cpu en sortie
  turn_on_SIM7080G();

  Serial.begin(115200); //9600

  Sim7080G.begin(Sim7080G_BAUDRATE, SERIAL_8N1, 20, 21);
  period1 = millis();

  //String mess = send_AT("AT+SIMCOMATI");
  //Serial.println(mess);
  Serial.println("toto");
  send_AT("AT+SIMCOMATI");
}

void loop() {
  everyXs();
  //send_AT("AT+SIMCOMATI");
}


//uint8_t toto = 5 - 248;  Overflow à 255
//Serial.println(toto);  Résultat = 13
//"AT+CPOWD=1"