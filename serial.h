SoftwareSerial _serial(RxD, TxD);

#define MAX_ROM_VAL 255

// Commands
#define PINGBACK 255
#define GET_TIME 254
#define SET_TIME 253
#define GET_NUM_SWITCH 252
#define GET_ROM_VAL 251

String readData;
int command = 0;
unsigned long prevMills = 0;

void enableConfigMode()
{
  _serial.begin(9600);

  delay(500);
}

void printError()
{
  _serial.println(-1);
}

void executeCommand(int command, String value)
{
  long val = value.toInt();

  // Indicates _serial is connected with master device
  // A callback to connected device for identification of this program
  if (command == PINGBACK)
  {
    _serial.println(PINGBACK);
  }

  // Get current time from RTC in timestamp
  else if (command == GET_TIME)
  {
    _serial.println(getTimeNow());
  }
  // Set RTC time, value in timestamp
  else if (command == SET_TIME && val > 0) {
    setTimeNow(val);
    delay(100);
    _serial.println(getTimeNow());
  }

  // Get num of switch device support
  else if (command == GET_NUM_SWITCH)
  {
    _serial.println(TOTAL_SWT);
  }
  
  // Read value from EEPROM
  else if (command == GET_ROM_VAL && (val >= 0 && val <= MAX_ROM_VAL))
  {
    _serial.println(getROMvalue(byte(val)));
  }

  // Write value to EEPROM
  else if (command >= 0 && command <= MAX_ROM_VAL && val >= 0 && val < MAX_ROM_VAL)
  {
    setROMvalue(command, byte(val));
    delay(50);
    _serial.println(getROMvalue(byte(command)));
  }
  else {
    printError();
  }
}

void analyzeData(String str)
{
  if (command > 0 && (millis() - prevMills < 2000)) {
    executeCommand(command, str);
    command = 0;
  }
  else {
    prevMills = millis();
    command = str.toInt();
  }
}

void runSerialMode()
{
  while (!_serial.available());
  
  while(_serial.available())
  {
    char c = _serial.read();
    readData += c;
    delay(10);
  }

  if(readData.length() > 0)
  {
    analyzeData(readData);
    readData = "";
  }
}
