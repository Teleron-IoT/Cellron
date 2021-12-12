#pragma once
#include <Arduino.h>

namespace EC25
{


    class atCommands{

        int receiveTO; 
        int isFinalResult(String response);
                
        
        public:
        HardwareSerial *modem;
        HardwareSerial *pc;
        atCommands(HardwareSerial *_modem, HardwareSerial *_pc);
        int sendCommand(String *command, String *response);
        int sendCommand(String *command);



        
        
    };

    class LTE:atCommands {

    public:
        LTE(HardwareSerial *_modem, HardwareSerial *_pc);
        void test();
        String text = "";
        String konum = "kalp";
        bool ping(String addr);
        bool sendHttpsReq(String addr, String *request);
        bool activatePDP();
        String buildPatchRequest(String *addr,String *data,String *path);
    };

    class gnss:atCommands {

        public:

    };

    class socketLTE:LTE {


        socketLTE(HardwareSerial *_modem, HardwareSerial *_pc);
        
    };
}