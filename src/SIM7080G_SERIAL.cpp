#include "SIM7080G_SERIAL.hpp"

String send_AT(String message, unsigned long timeout) {
    unsigned long startTime = millis();
    String uart_buffer = "";
    Sim7080G.println(message);
  
    while ((millis() - startTime < timeout) && (uart_buffer.endsWith("OK") == false)) {
        if (Sim7080G.available()) {
            uint8_t byte_recv = Sim7080G.read();
            uart_buffer += (char) byte_recv;
        }
    }
    return uart_buffer;
}

String send_AT(String message) {
    unsigned long startTime = millis();
    String uart_buffer = "";
    Sim7080G.println(message);
  
    while ((millis() - startTime < 1000) && (uart_buffer.endsWith("OK") == false)) {
        if (Sim7080G.available()) {
            uint8_t byte_recv = Sim7080G.read();
            uart_buffer += (char) byte_recv;
        }
    }
    return uart_buffer;
}