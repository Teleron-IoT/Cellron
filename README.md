
# Cellron - ESP32 LTE Geliştirme Kartı 

Cellron, ESP32-WROOM-32D tabanlı bir 4.5G LTE haberleşme kartıdır. Quectel EC25 modülünü kullanarak LTE üzerinden kolayca veri gönderip alabilirsiniz.



## Kütüphane Kullanımı

### 1- atCommands 
EC25'e istediğim AT komutlarını gönderebilmek ve aldığımız cevabı yorumlamak için gerekli fonksiyonlar bu sınıf içinde tanımlanmıştır.

#### atCommands(HardwareSerial *_modem, HardwareSerial *_pc)
EC25'i initialize etmek için kullanılır.

| Parametre | Tip     | Açıklama                |
| :-------- | :------- | :------------------------- |
| `_modem` | `HardwareSerial` | EC25'in bağlı olduğu serial port |
| `_pc` | `HardwareSerial` | Debug çıktılarını alacağınız cihazın bağlı olduğu serial port |

#### int sendCommand(String *command, String *response);
EC25'e AT komutlarını göndermek için kullanılır.
| Parametre | Tip     | Açıklama                |
| :-------- | :------- | :------------------------- |
| `command` | `String` | Gönderilecek Komut |
| `response` | `String` | Debug çıktılarını alacağınız cihazın bağlı olduğu serial port |
| `return` | `int` | Gelen cevabın kategorisi [1] |

#### int sendCommand(String *command);
EC25'e AT komutlarını göndermek için kullanılır. (Cevap yollanmaz)
| Parametre | Tip     | Açıklama                |
| :-------- | :------- | :------------------------- |
| `command` | `String` | Gönderilecek Komut |
| `return` | `int` | Gelen cevabın kategorisi [1] |

#### void listenPost();
EC25'den dönen cevaplar bitiş verisi gelene kadar dinlenir.

###2- LTE 
LTE kullanarak haberleşmek için kullanılan sınıf.
####LTE(HardwareSerial *_modem, HardwareSerial *_pc)
LTE'yi initialize eder.
| Parametre | Tip     | Açıklama                |
| :-------- | :------- | :------------------------- |
| `_modem` | `HardwareSerial` | EC25'in bağlı olduğu serial port |
| `_pc` | `HardwareSerial` | Debug çıktılarını alacağınız cihazın bağlı olduğu serial port |
#### void test();
Modül testi için SMS test fonksiyonu 
#### void activatePDP();
İnternet bağlantısını sağlamak için gerekli ayar fonksiyonu 
#### bool ping(String addr);
İstenilen adrese ping atılır.
| Parametre | Tip     | Açıklama                |
| :-------- | :------- | :------------------------- |
| `addr` | `String` | Ping atılacak adres |
| `return` | `bool` | Ping başarılı oldu mu |

#### bool sendHttpsReq(String addr, String *request);
İstenen adrese HTTPs isteği yollanır
| Parametre | Tip     | Açıklama                |
| :-------- | :------- | :------------------------- |
| `addr` | `String` | Bağlantı kurulacak adres |
| `request` | `String` | Gönderilecek HTTPs body |
| `return` | `bool` | İstek başarılı oldu mu |

## Örnek Kod

```cpp
#include <Arduino.h>
#include "EC25.h"

void setup() {
   Serial.begin(9600);
   EC25::LTE EC25Dev(&Serial2,&Serial);

  pinMode(5, OUTPUT);
  Serial.println("Setup");
  delay(3000);
  
  String text;
  EC25Dev.ping("google.com"); //Google'a ping atılır
  delay(1000);
  String addr = "oguzkagandeneme-fde40-default-rtdb.firebaseio.com"; //Verinin gönderileceği adres
  String data = "{ \"asd\" : \"asd\"}"; //Gönderilecek veri
  String path = "/in.json"; //Gönderilecek yol
  EC25Dev.sendHttpsReq(addr+path,&data);
}
```