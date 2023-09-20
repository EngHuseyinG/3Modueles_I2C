







#include "RTClib.h"  // Kütüphanemizi ekliyoruz
#include <Wire.h>
#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SH110X.h>
#include <Adafruit_AHTX0.h>

#define LOGO_HEIGHT 16
#define LOGO_WIDTH 16



static const unsigned char PROGMEM  wifi_icon[] =
{
	0b00000000, 0b00000000, //                 
	0b00000111, 0b11100000, //      ######     
	0b00011111, 0b11111000, //    ##########   
	0b00111111, 0b11111100, //   ############  
	0b01110000, 0b00001110, //  ###        ### 
	0b01100111, 0b11100110, //  ##  ######  ## 
	0b00001111, 0b11110000, //     ########    
	0b00011000, 0b00011000, //    ##      ##   
	0b00000011, 0b11000000, //       ####      
	0b00000111, 0b11100000, //      ######     
	0b00000100, 0b00100000, //      #    #     
	0b00000001, 0b10000000, //        ##       
	0b00000001, 0b10000000, //        ##       
	0b00000000, 0b00000000, //                 
	0b00000000, 0b00000000, //                 
	0b00000000, 0b00000000, //                 
};

const unsigned char mobile_icon[] =
{
	0b00000000, 0b00000000, //                 
	0b00000000, 0b00110000, //           ##    
	0b00000000, 0b00110000, //           ##    
	0b00001111, 0b11111000, //     #########   
	0b00001111, 0b11111000, //     #########   
	0b00001100, 0b00011000, //     ##     ##   
	0b00001100, 0b00011000, //     ##     ##   
	0b00001100, 0b00011000, //     ##     ##   
	0b00001100, 0b00011000, //     ##     ##   
	0b00001111, 0b11111000, //     #########   
	0b00001111, 0b11111000, //     #########   
	0b00001111, 0b11111000, //     #########   
	0b00001111, 0b11111000, //     #########   
	0b00001111, 0b11111000, //     #########   
	0b00001111, 0b11111000, //     #########   
	0b00001111, 0b11111000, //     #########   
};

const unsigned char bulb_on[] =
{
	0b00000000, 0b00000000, //                 
	0b00100011, 0b11100010, //   #   #####   # 
	0b00010100, 0b00010100, //    # #     # #  
	0b00001000, 0b00001000, //     #       #   
	0b00010000, 0b00000100, //    #         #  
	0b00010000, 0b00000100, //    #         #  
	0b00010000, 0b00000100, //    #         #  
	0b00010000, 0b00000100, //    #         #  
	0b00010000, 0b00000100, //    #         #  
	0b00001000, 0b00001000, //     #       #   
	0b00010100, 0b00010100, //    # #     # #  
	0b00100011, 0b11100010, //   #   #####   # 
	0b00000010, 0b00100000, //       #   #     
	0b00000011, 0b11100000, //       #####     
	0b00000010, 0b00100000, //       #   #     
	0b00000011, 0b11100000, //       #####     
};

const unsigned char bulb_off[] =
{
	0b00000000, 0b00000000, //                 
	0b00000011, 0b11100000, //       #####     
	0b00000111, 0b11110000, //      #######    
	0b00001111, 0b11111000, //     #########   
	0b00011111, 0b11111100, //    ###########  
	0b00011111, 0b11111100, //    ###########  
	0b00011111, 0b11111100, //    ###########  
	0b00011111, 0b11111100, //    ###########  
	0b00011111, 0b11111100, //    ###########  
	0b00001111, 0b11111000, //     #########   
	0b00000100, 0b00010000, //      #     #    
	0b00000011, 0b11100000, //       #####     
	0b00000010, 0b00100000, //       #   #     
	0b00000011, 0b11100000, //       #####     
	0b00000010, 0b00100000, //       #   #     
	0b00000011, 0b11100000, //       #####     
};


const unsigned char nocon_icon[] =
{
	0b00000000, 0b00000000, //                 
	0b00000011, 0b11100000, //       #####     
	0b00001111, 0b11111000, //     #########   
	0b00011111, 0b11111100, //    ###########  
	0b00111110, 0b00111110, //   #####   ##### 
	0b00111000, 0b01111110, //   ###    ###### 
	0b01110000, 0b11111111, //  ###    ########
	0b01110001, 0b11110111, //  ###   ##### ###
	0b01110011, 0b11000111, //  ###  ####   ###
	0b01110111, 0b10000111, //  ### ####    ###
	0b00111111, 0b00001110, //   ######    ### 
	0b00111110, 0b00011110, //   #####    #### 
	0b00011111, 0b11111100, //    ###########  
	0b00001111, 0b11111000, //     #########   
	0b00000011, 0b11100000, //       #####     
	0b00000000, 0b00000000, //                 
};


const unsigned char temperature_icon[] =
{
	0b00000001, 0b11000000, //        ###      
	0b00000011, 0b11100000, //       #####     
	0b00000111, 0b00100000, //      ###  #     
	0b00000111, 0b11100000, //      ######     
	0b00000111, 0b00100000, //      ###  #     
	0b00000111, 0b11100000, //      ######     
	0b00000111, 0b00100000, //      ###  #     
	0b00000111, 0b11100000, //      ######     
	0b00000111, 0b00100000, //      ###  #     
	0b00001111, 0b11110000, //     ########    
	0b00011111, 0b11111000, //    ##########   
	0b00011111, 0b11111000, //    ##########   
	0b00011111, 0b11111000, //    ##########   
	0b00011111, 0b11111000, //    ##########   
	0b00001111, 0b11110000, //     ########    
	0b00000111, 0b11100000, //      ######     
};


const unsigned char warning_icon[] =
{
	0b00000000, 0b10000000, //         #       
	0b00000001, 0b11000000, //        ###      
	0b00000001, 0b11000000, //        ###      
	0b00000011, 0b11100000, //       #####     
	0b00000011, 0b01100000, //       ## ##     
	0b00000111, 0b01110000, //      ### ###    
	0b00000110, 0b00110000, //      ##   ##    
	0b00001110, 0b10111000, //     ### # ###   
	0b00001100, 0b10011000, //     ##  #  ##   
	0b00011100, 0b10011100, //    ###  #  ###  
	0b00011000, 0b10001100, //    ##   #   ##  
	0b00111000, 0b00001110, //   ###       ### 
	0b00110000, 0b10000110, //   ##    #    ## 
	0b01111111, 0b11111111, //  ###############
	0b01111111, 0b11111111, //  ###############
	0b00000000, 0b00000000, //                 
};

// Adafruit'in RTClib kütüphanesi

RTC_DS1307 rtc;  // Kütüphanemiz başlatılıyor

char HaftaninGunleri[7][12] = { "Pazar", "Pazartesi", "Salı",
                                "Çarşamba", "Perşembe", "Cuma", "Cumartesi" };



Adafruit_AHTX0 aht;

#define i2c_Address 0x3C
#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
#define OLED_RESET -1   //   QT-PY / XIAO
Adafruit_SH1106G display = Adafruit_SH1106G(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

#define NUMFLAKES 10  // Number of snowflakes in the animation example

#define LOGO_HEIGHT 16
#define LOGO_WIDTH 16


void setup() {
  Serial.begin(115200);

  if (!display.begin(i2c_Address, true)) {
    Serial.println(F("SSD1306 allocation failed"));
    for (;;)
      ;  // Don't proceed, loop forever
  }

  display.clearDisplay();
  display.display();

  if (!aht.begin()) {
    Serial.println("Could not find AHT? Check wiring");
    while (1) delay(10);
  }
  Serial.println("AHT10 or AHT20 found");

  // Clear the buffer


  // Seri Port Ekranı'nı başlatıyoruz
  if (!rtc.begin()) {  // Modüle bağlantı kontrol ediliyor
    Serial.println("RTC Bulunamadı!");
    while (1)
      ;
  }
}
void loop() {
  // populate temp and humidity objects with fresh data
  DateTime now = rtc.now();    
                // Güncel saati bu satırda okuyoruz
  if (now.day() < 10) { Serial.print("0"); }  // 3. ayı 03 olarak gösterelim
  Serial.print(now.day(), DEC);               // Günü yazalım
  Serial.print(".");
  if (now.month() < 10) { Serial.print("0"); }
  Serial.print(now.month(), DEC);  // Ayı yazalım
  Serial.print(".");
  Serial.print(now.year(), DEC);  // Yılı yazalım
  Serial.print(" ");
  Serial.print(HaftaninGunleri[now.dayOfTheWeek()]);  // Günün adı
  Serial.print(" | ");
  if (now.hour() < 10) { Serial.print("0"); }
  Serial.print(now.hour(), DEC);  // Saati yazalım
  Serial.print(":");
  if (now.minute() < 10) { Serial.print("0"); }
  Serial.print(now.minute(), DEC);  // Dakikayı yazalım
  Serial.print(":");
  if (now.second() < 10) { Serial.print("0"); }
  Serial.println(now.second(), DEC);

  sensors_event_t humidity, temp;
  aht.getEvent(&humidity, &temp);

    display.clearDisplay();
   display.display();
    delay(1000);

    
   display.drawBitmap(0, 0, wifi_icon, 16, 16, 1);
   display.display();
    delay(100);
   display.drawBitmap(16, 0, mobile_icon, 16, 16, 1);
      display.display();
    delay(100);
   display.drawBitmap(32, 0, bulb_on, 16, 16, 1);
      display.display();
    delay(100);
   display.drawBitmap(48, 0, bulb_off, 16, 16, 1);
      display.display();
    delay(100);
    display.drawBitmap(64, 0, temperature_icon, 16, 16, 1);
       display.display();
    delay(100);
   display.drawBitmap(80, 0, warning_icon, 16, 16, 1);
      display.display();
    delay(100);
   display.drawBitmap(96, 0, nocon_icon, 16, 16, 1);
      display.display();
    delay(100);

  display.setTextSize(1);
  display.setTextColor(SH110X_WHITE);
 
  display.setCursor(0, 25);
  display.print(String(temp.temperature) + " C");
  
  display.setCursor(64, 25);
  display.print(String(humidity.relative_humidity) + " %");

  display.setCursor(0, 45);
  display.print(now.hour());
  display.print(".");
  display.print(now.minute());
    display.print(".");
  display.print(now.second());
  display.print("  ");

  display.print(now.day());
     display.print(".");
  display.print(now.month());
     display.print(".");
  display.print(now.year());




  // update display with all of the above graphics
  display.display();
  // Saniyeyi yazalım
  delay(1000);
}