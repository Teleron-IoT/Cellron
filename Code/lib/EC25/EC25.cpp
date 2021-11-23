#include "EC25.h"
#include <Arduino.h>


namespace EC25
{

    atCommands::atCommands(){
        Serial.begin(9600);
        Serial2.begin(115200, SERIAL_8N1, 16, 17);
    };

    bool atCommands::sendCommand(String *command, String *response){
        const char *line = "";

        Serial2.println("AT");
        Serial.println("AT");

        String text;

        while (1){

        if (Serial2.available() > 0) {
                // read the incoming byte:
                text = Serial2.readString();
                Serial.println(text);
        }
        }
        Serial2.println(*command);
        Serial.println(*command);




        while (!Serial2.available()==0);

        if (Serial2.available() > 0) {
                // read the incoming byte:
                text = Serial2.readStringUntil('\n');
                Serial.println(text);
        }
        // do {
        //     if (Serial2.available() > 0) {
        //         delay(5000);
        //     return true;
        //     }
        //     } while (!isFinalResult(line));
        Serial.println(*line);

            return true;
            
    };
    
    LTE::LTE(){
        
    };
    void LTE::test(){

        // Serial.println("AT+QGPSCFG");
        // Serial.println("AT+QGPS");
        // Serial.println("AT+QGPS"); 
        String *command = new String;
        String *response = new String;
        *command="AT+CSCS=\"GSM\"";
        atCommands::sendCommand(command, response);
        *command="AT+CMGS=\"+905348709253\"";
        atCommands::sendCommand(command, response);
        *command=konum;
        atCommands::sendCommand(command, response);
        *command="\x1a";
        atCommands::sendCommand(command, response);
        // Serial.println("AT+CSCS=\"GSM\"");
        // Serial.println("AT+CMGS=\"+905369837063\"");
        // Serial.println(konum);
        // Serial.println("\x1a");

//         if (Serial2.available() > 0) {
//         // read the incoming byte:
//         text = Serial2.readString();
//         Serial.println(text);
//   }
    };
}