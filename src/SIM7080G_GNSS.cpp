#include "SIM7080G_GNSS.hpp"
#include "time.h"

//struct tm time_gnss;

struct float_gnss {
    uint8_t entier;
    uint32_t decimal;
};

void setup_GNSS(){
    send_AT("AT+CGNSPWR=1");
    send_AT("AT+CGNSPWR=1,0,0,1,0");
}

String loop_GNSS(){
    String message = send_AT("AT+CGNSINF");
    return message;
}

String parse_GNSS_data(String mess) {
    struct tm time_gnss;
    String parsedData = "";
    uint16_t index = 0;
    uint64_t timestamp;
    struct float_gnss longitude;
    struct float_gnss latitude;

    uint16_t start = 0;
    for (u_int16_t i = 0; i < mess.length(); i++) {
        if (mess.charAt(i) == ',') {
            String field = mess.substring(start, i);
            if (field.length() > 0) {
                if (index > 0) {
                    parsedData += "\n";
                }
                if (index == 2) { // TIMESTAMP
                    String year = field.substring(0, 4);
                    time_gnss.tm_year = year.toInt() - 1900;
                    String month = field.substring(4, 6);
                    time_gnss.tm_mon = month.toInt() - 1;
                    String day = field.substring(6, 8);
                    time_gnss.tm_mday = day.toInt();
                    String hours = field.substring(8, 10);
                    time_gnss.tm_hour = hours.toInt();
                    String minutes = field.substring(10, 12);
                    time_gnss.tm_min = minutes.toInt();
                    String sec = field.substring(12, 14);
                    time_gnss.tm_sec = sec.toInt();
                }
                if (index == 3) { // Latitude
                    Serial.println("Latitude : " + field);
                    String latitude_str_1 = field.substring(0, field.indexOf('.'));
                    String latitude_str_2 = field.substring(field.indexOf('.') + 1, 9);
                    latitude.entier = latitude_str_1.toInt();
                    latitude.decimal = latitude_str_2.toInt();
                    Serial.println(latitude.entier);
                    Serial.println(latitude.decimal);
                }
                if (index == 4) { // Longitude
                    Serial.println("Longitude : " + field);
                    String longitude_str_1 = field.substring(0, field.indexOf('.'));
                    String longitude_str_2 = field.substring(field.indexOf('.') + 1, 8);
                    longitude.entier = longitude_str_1.toInt();
                    longitude.decimal = longitude_str_2.toInt();
                    Serial.println(longitude.entier);
                    Serial.println(longitude.decimal);
                }
                parsedData += field;
                index++;
            }
            start = i + 1;
        }
    }
    timestamp = mktime(&time_gnss);
    //Serial.println(timestamp);
    String lastField = mess.substring(start);
    if (lastField.length() > 0) {
        parsedData += lastField;
    }
    //Serial.println(parsedData);
    return parsedData;
}