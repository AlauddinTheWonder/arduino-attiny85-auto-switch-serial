/*
   Alauddin Ansari
   2020-09-23
   ATtiny85 Low-Powered Automate switches
   Dependencies:
   1. SoftwareSerial
   2. TinyRTC : https://github.com/AlauddinTheWonder/arduino-tiny_rtc.git
   3. TinyWireM
   4. EEPROM

   Build Size: 7096 bytes (ATtiny85, 8MHz);
*/

#include <EEPROM.h>
#include <SoftwareSerial.h>
#include <TinyRTC.h>

// Dependent files
/*
 serial.ino
 eep-rom.ino
 */
#include "config.h"
#include "watchdog.h"
#include "functions.h"
#include "time-function.h"
#include "eep-rom.h"
#include "serial.h"



void setup() {
  pinMode(ModePin, INPUT);

  if (digitalRead(ModePin)) {
    ConfigMode = true;
    enableConfigMode(); // serial.h
  }
  else {
    ConfigMode = false;

    for (uint8_t r = 0; r < TOTAL_SWT; r++)
    {
      uint8_t pin = Switches[r][0];

      pinMode(pin, OUTPUT);
      digitalWrite(pin, LOW);
    }

    connectRTC();
    setup_watchdog(wtd_mode);
  }

  initVarsFromRom();

  delay(500);
}

void loop() {
  if (ConfigMode) {
    runSerialMode();
  }
  else {
    if (wtd_cnt == 0) {

      tmElements_t tm = getTime();

      delay(100);

      if (validateTime(tm)) {

        byte _hour = tm.Hour;

        for (uint8_t r = 0; r < TOTAL_SWT; r++)
        {
          uint8_t pin = Switches[r][0];
          uint8_t on = Switches[r][1];
          uint8_t off = Switches[r][2];

          byte switch_status = getOnOffStatus(_hour, on, off);
          digitalWrite(pin, switch_status);
          delay(100);
        }

        delay(500);


        // Delay time to sync drifted time in RTC module
        if (_hour != last_hour) {
          if (initialized) { // Ignore initial call.

            // Sync drifted time
            // This will correct drifted second in every hour
            // Second must be less than 60 seconds.
            if (driftSecond > 0) {
              // Update RTC module time with adjusted time
              // In TimeFunctions.h file
              syncDriftedTime(driftSecond);
            }
          }
          last_hour = _hour;
        }

        initialized = true;
      }
    }

    wtd_cnt++;

    if (wtd_cnt >= wtd_cnt_reset) {
      wtd_cnt = 0;
    }

    system_sleep();
  }
}
