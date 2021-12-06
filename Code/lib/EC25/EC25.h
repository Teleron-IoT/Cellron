#pragma once
#include <Arduino.h>

namespace EC25
{


    class atCommands{

        int receiveTO; 
        bool isFinalResult(String response)
                {
                    switch (response.charAt(0)) {
                    case '+':
                        if (response.startsWith("+CME ERROR:")){
                            return true;
                        }
                        if (response.startsWith("+CMS ERROR:")) {
                            return true;
                        }
                        return false;
                    case 'B':
                        if (response.startsWith("BUSY\r\n") == 0) {
                            return true;
                        }
                        return false;

                    case 'E':
                        if (response.startsWith("ERROR\r\n") == 0) {
                            return true;
                        }
                        return false;
                    case 'N':
                        if (response.startsWith("NO ANSWER\r\n") == 0) {
                            return true;
                        }
                        if (response.startsWith("NO CARRIER\r\n") == 0) {
                            return true;
                        }
                        if (response.startsWith("NO DIALTONE\r\n") == 0) {
                            return true;
                        }
                        return false;
                    case 'O':
                        if (response.startsWith("OK\r\n") == 0) {
                            return true;
                        }
                    case '>':
                        return true;
                    default:
                        return false;
                    }

                }
        
        public:
        HardwareSerial *modem;
        HardwareSerial *pc;
        atCommands(HardwareSerial *_modem, HardwareSerial *_pc);
        bool sendCommand(String *command, String *response);
        bool sendCommand(String *command);



        
        
    };

    class LTE:atCommands {

    public:
        LTE(HardwareSerial *_modem, HardwareSerial *_pc);
        void test();
        String text = "";
        String konum = "kalp";
    };

    class gnss:atCommands {

        public:

    };

    class socketLTE:LTE {


        socketLTE(HardwareSerial *_modem, HardwareSerial *_pc);
        
    };
}