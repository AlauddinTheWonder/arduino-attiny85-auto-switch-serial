// Watchdog Settings
#define wtd_mode 9        // 6=1sec (0.5sec), 7=2sec (1sec), 8=4sec (3.2sec), 9=8sec (7.4sec)
#define wtd_cnt_reset 75  // Actual task will be executed after this counter.
byte wtd_cnt = 0;         // Counter for task execution comparision.


/*
   Pins Setting
   -------------------------
   Pin0 - RTC SDA (Phy Pin5) - occupied
   Pin2 - RTC SCL (Phy Pin7) - occupied
*/

#define TOTAL_SWT 3     // 3 Pin controller
#define RxD 3 // SerialDevice Tx
#define TxD 4 // SerialDevice Rx
#define ModePin 1       // with 10K to Gnd. VCC to enable BT mode


// Time schedule (in Hour) -- Same on and off value means disable
// Switches                    = { Pin, OnHour, OffHour }
uint8_t Switches[TOTAL_SWT][3] = { {1, 6, 23}, {3, 9, 19}, {4, 8, 0} };
uint8_t driftSecond = 1;      // To adjust RTC time drift in seconds. Many RTC drift time. 


boolean ConfigMode = false;   // indicate whether setting mode is enabled or not
boolean initialized = false;  // Flag to check whether running first time after powering up, used in sync time drift.
int last_hour = -1;           // Last hour to compare current hour change, used in sync time drift.
