#include <LoRa.h>
#include <SPI.h>
#include <Arduino.h>
#include <TFT_eSPI.h> // Graphics and font library for ILI9341 driver chip

#define ss 5
#define rst 14
#define dio0 21

#define TFT_GREY 0x5AEB // New colour

TFT_eSPI TFT = TFT_eSPI();

TFT_eSprite eSprite = TFT_eSprite(&TFT);

void setup()
{
  setup_screen();
  setup_lora();
}

void setup_screen()
{
  TFT.init();
  TFT.setRotation(1);
  TFT.fillScreen(TFT_BLUE);
  TFT.initDMA();
  eSprite.setTextFont(1);
  eSprite.setTextColor(TFT_WHITE);
  eSprite.createSprite(240, 240);
}

void setup_lora()
{
  Serial.begin(115200);
  while (!Serial)
    ;
  Serial.println("LoRa Receiver");

  LoRa.setPins(ss, rst, dio0); //setup LoRa transceiver module

  while (!LoRa.begin(433E6)) //433E6 - Asia, 866E6 - Europe, 915E6 - North America
  {
    Serial.println(".");
    delay(500);
  }
  LoRa.setSyncWord(0xA5);
  Serial.println("LoRa Initializing OK!");
}

void loop()
{
  loop_screen();
}

void loop_screen()
{
  eSprite.setTextFont(1);
  eSprite.setCursor(20, 20);
  eSprite.println("Hello World\n");
  eSprite.setCursor(40, 40);
  eSprite.println("Hello World\n");
  eSprite.pushSprite(0, 0);
  delay(1000);
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
    }
    Serial.print("' with RSSI "); // print RSSI of packet
    Serial.println(LoRa.packetRssi());
  }

}