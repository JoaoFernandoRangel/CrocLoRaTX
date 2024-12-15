#include <Arduino.h>
#include <LoRa.h>
#include <SPI.h>

#define PotPin A4
#define noiseThrs 25
#define idMAX 5
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
    LoRa.setSyncWord(0xF3);
    potRead = analogRead(PotPin);
    Serial.println("Finish Setup");
}

String sender = "Sending packet: ";
void loop() {
    // if (handleAnalogRead(PotPin, potRead, noiseThrs)) {
    //     Serial.print("Sending packet: ");
    //     Serial.println(potRead);
    //     counter++;
    //     sendString(String(potRead));
    // }
    if (millis() - t[0] > 5000) {
        float value[idMAX];
        String toGo;
        int i = 0;
        while (i < idMAX) {
            value[i] = (static_cast<float>(random(0, 100)) + 0.01 * static_cast<float>(random(0, 50)));
            toGo += "id" + String(i) + "_" + value[i] + ";";
            i++;
        }
        toGo += "id" + String(idMAX) + "_" + counter + ";";
        Serial.print("Sending packet: ");
        Serial.println(toGo);
        sendString(toGo);
        counter++;
        t[0] = millis();
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