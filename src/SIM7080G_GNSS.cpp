#include "SIM7080G_GNSS.hpp"

void setup_GNSS(){
    send_AT("AT+CGNSPWR=1");
    send_AT("AT+CGNSPWR=1,0,0,1,0");
}

String loop_GNSS(){
    String message = send_AT("AT+CGNSINF");
    return message;
}

void parse_GNSS_data(String mess) {
    String parsedData[17];
    int index = 0;
  
    // Split le message par virgule
    int start = 0;
    for (int i = 0; i < mess.length(); i++) {
        if (mess.charAt(i) == ',') {
            // Extraire la chaine
            String field = mess.substring(start, i);
            // Stocker les chaines non vides
            if (field.length() > 0) {
                parsedData[index++] = field;
            }
            start = i + 1;
        }
    }
    // Ajouter le dernier champ
    String lastField = mess.substring(start);
    if (lastField.length() > 0) {
        parsedData[index++] = lastField;
    }
    // Afficher les données
    for (int j = 0; j < index; j++) {
        Serial.println(parsedData[j]);
    }
}