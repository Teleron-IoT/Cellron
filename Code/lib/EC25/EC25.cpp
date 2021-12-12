#include "EC25.h"
#include <Arduino.h>


namespace EC25
{

    atCommands::atCommands(HardwareSerial *_modem, HardwareSerial *_pc){
        modem = _modem;
        pc = _pc;
        modem->begin(115200, SERIAL_8N1, 16, 17);
    };

    int atCommands::sendCommand(String *command, String *response){

        modem->println(*command);

        while (modem->available()==0);
        *response ="";

        int res = 0;
        do {
            delay(1000);
            if (modem->available() > 0) {
                *response = modem->readStringUntil('\n');
                pc->println(*response);
                
            }
            res = isFinalResult(*response);
        } while (!res);
        return res;
            
    };
    
    int atCommands::sendCommand(String *command){

        modem->println(*command);

        while (modem->available()==0);
        String response ="";

        int res = 0;
        do {
            delay(1000);
            if (modem->available() > 0) {
                response = modem->readStringUntil('\n');
                pc->println(response);
                
            }
            res = isFinalResult(response);
        } while (!res);
        return res;
            
    };

    LTE::LTE(HardwareSerial *_modem, HardwareSerial *_pc):atCommands(_modem, _pc){
        
    };
    void LTE::test(){

        String *command = new String;
        *command="AT";
        atCommands::sendCommand(command);
        *command="AT+CSCS=\"GSM\"";
        atCommands::sendCommand(command);
        *command="AT+CMGF=1";
        atCommands::sendCommand(command);
        *command="AT+CMGS=\"+905369837063\"";
        atCommands::sendCommand(command);
        *command=konum;
        atCommands::sendCommand(command);
        *command="\x1a";
        atCommands::sendCommand(command);
    };
    
    bool LTE::activatePDP(){
        String *command = new String;
        *command="AT+QIACT?";
        atCommands::sendCommand(command);
        *command="AT+QICSGP=1";
        atCommands::sendCommand(command);
        *command="AT+QIACT=1";
        atCommands::sendCommand(command);
        *command="AT+QIACT?";
        atCommands::sendCommand(command);
        // if(atCommands::sendCommand(command)==2){
        //     *command="AT+QIACT=1";
        //     atCommands::sendCommand(command);
        //     *command="AT+QIACT?";
        //     if(atCommands::sendCommand(command)==2){
        //         return false;
        //     }
        // }
        return true;
        
        
    };
    bool LTE::sendHttpsReq(String addr, String *request){
        
    };
    String LTE::buildPatchRequest(String *addr,String *data,String *path){
        
        String req;
        req = "PATCH "+*path + (" HTTP/1.1\r\n"
        "Host: " +*addr+ (" \r\n"
        "Content-Type: application/json\r\n"
        "User-Agent: 1\r\n"
        "Accept: */* \r\n"
        "Cache-Control: no-cache\r\n"
        "accept-encoding: gzip, deflate\r\n"
        "content-length: "));
        req = req + data->length() + (
        "\r\n"
        "Connection: keep-alive\r\n"
        "cache-control: no-cache\r\n"
        "\r\n");
        req = req + *data;
        return req;

    };


    bool LTE::ping(String addr){
        String *command = new String;
        *command="AT";
        atCommands::sendCommand(command);
        activatePDP();
        *command="AT+QPING=1,\"172.217.169.174\",255,1";
        while(atCommands::sendCommand(command)!=1){
            *command="AT+QIDEACT=1";       
            atCommands::sendCommand(command);     
            activatePDP();
            *command="AT+QPING=1,\"172.217.169.174\",255,1";
            delay(100);
        };
        *command="AT+QIDEACT=1";
        atCommands::sendCommand(command);
        return 1;
    };

    int atCommands::isFinalResult(String response)
                {
                    switch (response.charAt(0)) {
                    case '+':
                        if (response.startsWith("+CME ERROR:")){
                            return 2;
                        }
                        if (response.startsWith("+CMS ERROR:")) {
                            return 2;
                        }
                        return false;
                    case 'B':
                        if (response.startsWith("BUSY\r\n") == 0) {
                            return 2;
                        }
                        return false;

                    case 'E':
                        if (response.startsWith("ERROR\r\n") == 0) {
                            return 2;
                        }
                        return false;
                    case 'N':
                        if (response.startsWith("NO ANSWER\r\n") == 0) {
                            return 2;
                        }
                        if (response.startsWith("NO CARRIER\r\n") == 0) {
                            return 2;
                        }
                        if (response.startsWith("NO DIALTONE\r\n") == 0) {
                            return 2;
                        }
                        return false;
                    case 'O':
                        if (response.startsWith("OK\r\n") == 0) {
                            return 1;
                        }
                    case '>':
                        return 1;
                    default:
                        return 0;
                    }

                }
}