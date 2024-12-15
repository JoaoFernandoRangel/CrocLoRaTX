#include <Arduino.h>
#include <LoRa.h>
#include <SPI.h>

#define PotPin A4
#define noiseThrs 20
void sendString(String send);
bool handleAnalogRead(uint8_t pin, int &pot, int noise);

unsigned long t[5];
uint16_t counter;
int potRead;

void setup() {
    Serial.begin(9600);
    Serial.println("Init Setup");
    Serial.println("LoRa Sender");
    pinMode(PotPin, INPUT);
    if (!LoRa.begin(433E6)) {
        Serial.println("Starting LoRa failed!");
        while (1);
    }
    // LoRa.setSyncWord(0xF3);
    potRead = analogRead(PotPin);
    Serial.println("Finish Setup");
}

String sender = "Sending packet: ";
void loop() {
  if(handleAnalogRead(PotPin, potRead, noiseThrs)){
    Serial.print("Sending packet: ");
    Serial.println(potRead);
    sendString(String(potRead));
  }
}

bool handleAnalogRead(uint8_t pin, int &pot, int noise) {
    int read1 = analogRead(pin);
    if (abs((abs(read1) - abs(pot))) > noise) {
        pot = read1;
        return true;
    } else {
        return false;
    }
}

void sendString(String send) {
    LoRa.beginPacket();
    LoRa.print(send.c_str());
    LoRa.endPacket();
}