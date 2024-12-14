#include <Arduino.h>
#include <SPI.h>
#include <LoRa.h>

void sendString(String send);

unsigned long t[5];
uint16_t counter;

void setup()
{
  Serial.begin(9600);
  while (!Serial)
    ;

  Serial.println("LoRa Sender");

  if (!LoRa.begin(915E6))
  {
    Serial.println("Starting LoRa failed!");
    while (1)
      ;
  }
}

void loop()
{
  String sender = "Sending packet: ";
  Serial.print("Sending packet: ");
  Serial.println(counter);


  sendString(sender + String(counter));

  counter++;

  delay(5000);
}

void sendString(String send)
{
  LoRa.beginPacket();
  LoRa.print(send.c_str());
  LoRa.endPacket();
}