#include <LoRa.h>
#include <SPI.h>
#include <Arduino.h>
#include <TFT_eSPI.h> // Graphics and font library for ILI9341 driver chip

#define SS 5
#define RST 22
#define DIO0 21

#define SCK 18
#define MISO 19
#define MOSI 23


SPIClass LoRaSPI;

#define TFT_GREY 0x5AEB // New colour
TFT_eSPI tft = TFT_eSPI();  // Invoke library

void setup()
{
  setup_lora();
  setup_screen();
}

void setup_lora()
{
  Serial.begin(115200);

  LoRaSPI.begin(SCK, MISO, MOSI, SS);
  LoRa.setSPI(LoRaSPI);
  LoRa.setPins(SS, RST, DIO0); //setup LoRa transceiver module

  while (!LoRa.begin(433E6)) //433E6 - Asia, 866E6 - Europe, 915E6 - North America
  {
    Serial.println(".");
    delay(500);
  }
  LoRa.setSyncWord(0xA5);
  Serial.println("LoRa Initializing OK!");
}


void setup_screen()
{
   tft.init();
   tft.setRotation(2);
}


void loop()
{
  loop_lora();
//  loop_screen();
}

void loop_screen()
{
 // Fill screen with grey so we can see the effect of printing with and without
   // a background colour defined
   tft.fillScreen(TFT_GREY);

   // Set "cursor" at top left corner of display (0,0) and select font 2
   // (cursor will move to next line automatically during printing with 'tft.println'
   //  or stay on the line is there is room for the text with tft.print)
   tft.setCursor(0, 0, 2);
   // Set the font colour to be white with a black background, set text size multiplier to 1
   tft.setTextColor(TFT_WHITE,TFT_BLACK);  tft.setTextSize(1);
   // We can now plot text on screen using the "print" class
//   tft.println("Hello World!");
}

void loop_lora()
{
  int packetSize = LoRa.parsePacket(); // try to parse packet
  if (packetSize)
  {
    Serial.print("Received packet '");

    while (LoRa.available()) // read packet
    {
      String LoRaData = LoRa.readString();
      Serial.print(LoRaData);

      tft.fillScreen(TFT_GREY);
      tft.setCursor(0, 0, 2);
      tft.setTextColor(TFT_WHITE,TFT_BLACK);  tft.setTextSize(2);
      tft.println("receive data:");
      tft.println(LoRaData);
    }

    Serial.print("' with RSSI "); // print RSSI of packet
    Serial.println(LoRa.packetRssi());
  }

}