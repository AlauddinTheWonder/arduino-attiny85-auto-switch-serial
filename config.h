/*
   Pins Setting
   -------------------------
   Pin0 - RTC SDA (Phy Pin5) - occupied
   Pin2 - RTC SCL (Phy Pin7) - occupied
   Pin1 - Mode Pin
   Pin3 - Serial Device Tx
   Pin4 - Serial Device Rx

 *              -.----
 *         RST -|    |- VCC
 * S2 / Tx - 3 -|    |- 2 - RTC SCL
 * S3 / Rx - 4 -|    |- 1 - S1 / Mode Pin
 *         GND -|    |- 0 - RTC SDA
 *              ------
*/

// AtTiny85 I/O pins
#define SWT_1 1
#define SWT_2 3
#define SWT_3 4

#define MODE_PIN 1       // with 10K to Gnd. VCC to enable Config mode
#define RxD 3           // SerialDevice Tx
#define TxD 4           // SerialDevice Rx

#define TOTAL_SWT 3     // 3 Pin controller
#define MAX_SETTINGS 10 // Number of settings saved


/** 
 * Time schedule (in Hour) -- Same on and off value means disable
 * Switches = { Pin, OnHour, OffHour }
 * Device: 001 => 1 = Extra, 2 = Light, 3 = Filter
 */

const int PinArray[TOTAL_SWT] = { SWT_1, SWT_2, SWT_3 };

uint8_t Switches[MAX_SETTINGS][3] = {
  {SWT_1, 0, 0},
  {SWT_2, 10, 18},
  {SWT_3, 6, 10},
  {SWT_3, 11, 13},
  {SWT_3, 14, 17},
  {SWT_3, 18, 20},
  {SWT_3, 21, 0},
  {0, 0, 0},
  {0, 0, 0},
  {0, 0, 0}
};
