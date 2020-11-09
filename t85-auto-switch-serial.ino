/*
   Alauddin Ansari
   2020-09-23
   ATtiny85 Low-Powered Automate switches
   Dependencies:
   1. SoftwareSerial
   2. TinyRTC : https://github.com/AlauddinTheWonder/arduino-tiny_rtc.git
   3. TinyWireM
   4. EEPROM

   Build Size: 5606 bytes (ATtiny85, 8MHz);
*/

#include <EEPROM.h>
#include <SoftwareSerial.h>
#include <TinyRTC.h>

// Dependent files
#include "config.h"
#include "watchdog.h"
#include "functions.h"
#include "time-function.h"
#include "eep-rom.h"
#include "serial.h"


// Watchdog Settings
#define WD_MODE 9        // 6=1sec (0.5sec), 7=2sec (1sec), 8=4sec (3.2sec), 9=8sec (7.4sec)
#define WD_CNT_RESET 75  // Actual task will be executed after this counter.
uint8_t wtd_cnt = 0;         // Counter for task execution comparision.
boolean ConfigMode = false;   // indicate whether config mode is enabled or not

void setup() {
  pinMode(MODE_PIN, INPUT);

  if (digitalRead(MODE_PIN)) {
    ConfigMode = true;
    enableConfigMode(); // serial.h
  }
  else {
    ConfigMode = false;

    for (uint8_t r = 0; r < TOTAL_SWT; r++)
    {
      pinMode(PinArray[r], OUTPUT);
      digitalWrite(PinArray[r], LOW);
    }

    connectRTC();
    setup_watchdog(WD_MODE);
  }

  initVarsFromRom();

  delay(500);
}

void loop() {
  if (ConfigMode) {
    runSerialMode(); // serial.h
  }
  else {
    if (wtd_cnt == 0) {

      tmElements_t tm = getTime();

      delay(100);

      uint8_t _hour = tm.Hour;

      uint8_t swt[TOTAL_SWT] = {}; // Initialized with 0

      // Calculating switch on/off status
      for (uint8_t b = 0; b < MAX_SETTINGS; b++)
      {
        if (Switches[b][0] <= TOTAL_SWT) {
          uint8_t swt_status = getOnOffStatus(_hour, Switches[b][1], Switches[b][2]);
          
          if (swt_status == 1) {
            swt[Switches[b][0] - 1] = 1;
          }
        }
      }

      // Setting switch on/off
      for (uint8_t c = 0; c < TOTAL_SWT; c++)
      {
        digitalWrite(PinArray[c], swt[c]);
        delay(100);
      }
    }

    wtd_cnt++;

    if (wtd_cnt >= WD_CNT_RESET) {
      wtd_cnt = 0;
    }

    system_sleep();
  }
}
