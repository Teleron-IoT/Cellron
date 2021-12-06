#include "EC25.h"
#include <Arduino.h>


namespace EC25
{

    atCommands::atCommands(HardwareSerial *_modem, HardwareSerial *_pc){
        modem = _modem;
        pc = _pc;
        modem->begin(115200, SERIAL_8N1, 16, 17);
    };

    bool atCommands::sendCommand(String *command, String *response){

        modem->println(*command);

        while (modem->available()==0);
        *response ="";
        do {
            delay(1000);
            if (modem->available() > 0) {
                *response = modem->readStringUntil('\n');
                pc->println(*response);
                
            }
        } while (!isFinalResult(*response));
        return true;
            
    };
    
    LTE::LTE(HardwareSerial *_modem, HardwareSerial *_pc):atCommands(_modem, _pc){
        
    };
    void LTE::test(){

        String *command = new String;
        String *response = new String;
        *command="AT+CSCS=\"GSM\"";
        atCommands::sendCommand(command, response);
        *command="AT+CMGF=1";
        atCommands::sendCommand(command, response);
        *command="AT+CMGS=\"+905369837063\"";
        atCommands::sendCommand(command, response);
        *command=konum;
        atCommands::sendCommand(command, response);
        *command="\x1a";
        atCommands::sendCommand(command, response);
    };
}