#include "WiFiServer.h"
#include "WiFiClientSecure.h"
#include <odroid_go.h>

const uint32_t pause = 0;

const uint32_t sol1 = 784;
const uint32_t fa1 = 698;
const uint32_t mi1 = 659;
const uint32_t re1 = 587;
const uint32_t do1 = 523;
const uint32_t si0 = 494;
const uint32_t la0 = 440;
const uint32_t sol0 = 392;
const uint32_t fa0 = 349;
const uint32_t mi0 = 330;
const uint32_t re0 = 294;
const uint32_t do0 = 262;
const uint32_t si_1 = 247;

const uint32_t gn = 500;
const uint32_t binden = 0;
const uint32_t stossen = 50;

const uint32_t NotenDauer[] = {

  sol0, gn*2, stossen,
  fa0, gn*2, stossen,
  mi0, gn*4, stossen,
  re0, gn, stossen,
  mi0, gn, stossen,
  fa0, gn, stossen,
  re0, gn, stossen,
  do0, gn*4, stossen,

  mi0, gn, stossen,
  fa0, gn, stossen,
  sol0, gn, stossen,
  mi0, gn, stossen,
  re0, gn, stossen,
  mi0, gn, stossen,
  fa0, gn, stossen,
  re0, gn, stossen,

  mi0, gn, stossen,
  fa0, gn, stossen,
  sol0, gn, stossen,
  mi0, gn, stossen,
  re0, gn, stossen,
  mi0, gn, stossen,
  fa0, gn, stossen,
  re0, gn, stossen,

  sol0, gn*2, binden,
  fa0, gn*2, binden,
  mi0, gn*4, binden,
  re0, gn, binden,
  mi0, gn, binden,
  fa0, gn, binden,
  re0, gn, binden,
  do0, gn*4, binden,

  do0, gn, binden,
  re0, gn, binden,
  mi0, gn, binden,
  fa0, gn, binden,
  sol0, gn, binden,
  la0, gn, binden,
  si0, gn, binden,
  do1, gn, binden,
  re1, gn, binden,
  mi1, gn, binden,
  fa1, gn, binden,
  sol1, gn, binden,
};

uint32_t NotenDauerIndex;
uint32_t DauerStop;
uint32_t DauerStossenStop;

void setup() {
  // put your setup code here, to run once:
  GO.begin();
  GO.lcd.clearDisplay();
  GO.lcd.println("setVolume 8");
  GO.Speaker.setVolume(5);
  NotenDauerIndex = 0;
  DauerStop = 0;
  DauerStossenStop = 0;
}

void loop() {
  // put your main code here, to run repeatedly:
  if (millis() > DauerStossenStop) {
    GO.Speaker.mute();
  }
  if (millis() > DauerStop) {
    // play the actual note
    GO.lcd.print("play note ");
    GO.lcd.print(NotenDauerIndex);
    GO.lcd.print(", ");
    GO.lcd.print(NotenDauer[NotenDauerIndex]);
    GO.lcd.print(" hz ");
    if (NotenDauer[NotenDauerIndex] == 0) {
      // play pause
      GO.Speaker.mute();
    } else {
      // play tone
      GO.Speaker.tone(NotenDauer[NotenDauerIndex]);
    }
    // move pointer to actual duration
    NotenDauerIndex++;
    GO.lcd.println(NotenDauer[NotenDauerIndex]);
    GO.lcd.print(" ms");
    GO.lcd.println();
    DauerStop = millis() + NotenDauer[NotenDauerIndex];
    // move pointer to actual stossen/binden
    NotenDauerIndex++;
    DauerStossenStop = DauerStop - NotenDauer[NotenDauerIndex];
    // move pointer to next note
    NotenDauerIndex++;
  }

  if (NotenDauerIndex >= sizeof(NotenDauer) / sizeof(NotenDauer[0])) {
    // song is over, start again
    NotenDauerIndex = 0;
  }
  
  GO.update();
}