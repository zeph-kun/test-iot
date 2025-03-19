#include "SIM7080G_SERIAL.hpp"
#include <Arduino.h>

void setup_GNSS();
String loop_GNSS();
String parse_GNSS_data(String mess);
String get_timestamp_and_pos(String mess);