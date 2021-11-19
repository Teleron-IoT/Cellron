#pragma once
#include <Arduino.h>

namespace EC25
{


    class atCommands{
        static bool is_final_result(const char * const response)
        {
        #define STARTS_WITH(a, b) ( strncmp((a), (b), strlen(b)) == 0)
            switch (response[0]) {
            case '+':
                if (STARTS_WITH(&response[1], "CME ERROR:")) {
                    return true;
                }
                if (STARTS_WITH(&response[1], "CMS ERROR:")) {
                    return true;
                }
                return false;
            case 'B':
                if (strcmp(&response[1], "USY\r\n") == 0) {
                    return true;
                }
                return false;

            case 'E':
                if (strcmp(&response[1], "RROR\r\n") == 0) {
                    return true;
                }
                return false;
            case 'N':
                if (strcmp(&response[1], "O ANSWER\r\n") == 0) {
                    return true;
                }
                if (strcmp(&response[1], "O CARRIER\r\n") == 0) {
                    return true;
                }
                if (strcmp(&response[1], "O DIALTONE\r\n") == 0) {
                    return true;
                }
                return false;
            case 'O':
                if (strcmp(&response[1], "K\r\n") == 0) {
                    return true;
                }
            default:
                return false;
            }

        }
        
    };

    class LTE {

    public:
        LTE();
        void test();
        String text = "";
        String konum = "";
    };

    class socketLTE:LTE {


        socketLTE();
        
    };
}