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
        pc->println(res);
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
        String *command = new String;
        *command="AT+QHTTPCFG=\"sslctxid\",1 ";
        atCommands::sendCommand(command);
        *command="AT+QSSLCFG=\"sslversion\",1,4";
        atCommands::sendCommand(command);
        *command="AT+QSSLCFG=\"ciphersuite\",1,0xFFFF";
        atCommands::sendCommand(command);
        *command="AT+QSSLCFG=\"seclevel\",1,0";
        atCommands::sendCommand(command);
        *command="AT+QSSLCFG=\"cacert\",1,\"RAM:cacert.pem\"";
        atCommands::sendCommand(command);
        *command="AT+QSSLCFG=\"clientcert\",1,\"RAM:clientcert.pem\"";
        atCommands::sendCommand(command);
        *command="AT+QSSLCFG=\"clientkey\",1,\"RAM:clientkey.pem\"";
        atCommands::sendCommand(command);
        *command="https://"+addr;
        *command="AT+QHTTPURL="+String(command->length())+",80";
        if(atCommands::sendCommand(command)==3){
            *command="https://"+addr;
            modem->println(*command);
            delay(200);
            *command="\x1a";
            atCommands::sendCommand(command);
        }else{return false;}
        
        // *command="AT+QHTTPURL?";
        // atCommands::sendCommand(command);

        *command="AT+QHTTPPOST="+String(request->length())+",80,80";
        if (atCommands::sendCommand(command)==3)
        {
            modem->println(*request);
            pc->println(*request);
            delay(200);
            // *command="\x1a";
            // atCommands::sendCommand(command);
            atCommands::listenPost();

        }else{return false;}        
        
        *command="AT+QHTTPREAD=80";
        atCommands::sendCommand(command);
        atCommands::listenPost();
        return true;
    };
    // String *LTE::buildPatchRequest(String *addr,String *data,String *path){
        
    //     String *req = new String;
    //     // *req = "PATCH "+*path + (" HTTP/1.1\r\n"
    //     // "Host: " +*addr+ (" \r\n"
    //     // "Content-Type: text/plain\r\n"
    //     // "content-length: "));
    //     // *req = *req + String(data->length()+2) + (
    //     // "\r\n");
    //     // *req = *req + *data;
    //     *req= "{\"asad\" : \"aasd\"}";
    //     return req;

    // };


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

    void atCommands::listenPost(){
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
        } while (res!=1);
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
                    case 'C':
                        if (response.startsWith("CONNECT") == 0) {
                            return 3;
                        }
                    case '>':
                        return 3;
                    default:
                        return 0;
                    }

                }
}