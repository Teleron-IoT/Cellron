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
        bool activatePDP();
    };

    class gnss:atCommands {

        public:

    };

    class socketLTE:LTE {


        socketLTE(HardwareSerial *_modem, HardwareSerial *_pc);
        
    };
}