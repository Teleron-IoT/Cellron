#pragma once
#include <Arduino.h>

namespace EC25
{

    //AT komutları bu sınıfta tanımlanır
    class atCommands{

        int receiveTO; 
        int isFinalResult(String response);
                
        
        public:
        HardwareSerial *modem;
        HardwareSerial *pc;
        atCommands(HardwareSerial *_modem, HardwareSerial *_pc); //EC25 ve UART haberleşmeleri ayarlanır
        int sendCommand(String *command, String *response); // Komut göndererek gelen cevabı alır
        int sendCommand(String *command); //Cevaba bakmaksızın komut gönderilir
        void listenPost(); //Dönen cevap dinlenir
    };


    //LTE haberleşmesi sınıfı
    class LTE:atCommands {
    public:
        LTE(HardwareSerial *_modem, HardwareSerial *_pc);
        void test(); //Modül testi için SMS test fonksiyonu 
        String konum = "test"; 
        bool ping(String addr); //Ping atarak bağlantı test etme fonksiyonu
        bool sendHttpsReq(String addr, String *request); //İstenen adrese HTTPs bağlantı sağlar
        bool activatePDP(); //İnternet bağlantısını sağlamak için gerekli ayar fonksiyonu 
        // String *buildPatchRequest(String *addr,String *data,String *path);
    };

    //GNSS sınıfı
    class gnss:atCommands {
        public:

    };

    //TCP-UDP soket sınıfı
    class socketLTE:LTE {

        socketLTE(HardwareSerial *_modem, HardwareSerial *_pc);
        
    };
}