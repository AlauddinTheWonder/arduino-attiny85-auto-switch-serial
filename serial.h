SoftwareSerial _serial(RxD, TxD);

#define MAX_ROM_VAL 255
#define CHAR_LEN 15

// Commands
#define PINGBACK 255
#define GET_TIME 254
#define SET_TIME 253
#define GET_NUM_SWITCH 252
#define GET_MAX_SETTINGS 251
#define GET_ROM_VAL 250

const char SymbCol = ':';
const char SymbPipe = '|';

void enableConfigMode()
{
  _serial.begin(9600);
  delay(500);
}

void executeCommand(uint8_t command, char * value)
{
  uint8_t val_i = atoi(value);
  uint32_t val_l = atol(value);
  
  if (command == PINGBACK)
  {
    _serial.print(GET_TIME);
    _serial.print(SymbCol);
    _serial.print(getTimeNow());
    _serial.print(SymbPipe);

    _serial.print(GET_NUM_SWITCH);
    _serial.print(SymbCol);
    _serial.print(TOTAL_SWT);
    _serial.print(SymbPipe);

    _serial.print(GET_MAX_SETTINGS);
    _serial.print(SymbCol);
    _serial.print(MAX_SETTINGS);
    _serial.print(SymbPipe);
    
    uint8_t cnt = 1;
    for (uint8_t r = 0; r < MAX_SETTINGS; r++)
    {
      for (uint8_t c = 0; c <= 2; c++) // 0=Pin, 1=On, 2=Off
      {
        _serial.print(cnt);
        _serial.print(SymbCol);
        _serial.print(getROMvalue(cnt));
        _serial.print(SymbPipe);
        cnt++;
      }
    }
    _serial.println("");
  }

  // Get current time from RTC in timestamp
  else if (command == GET_TIME)
  {
    _serial.println(getTimeNow());
  }
  // Set RTC time, value in timestamp
  else if (command == SET_TIME && value > 0) {
    setTimeNow(val_l);
    delay(100);
    _serial.println(getTimeNow());
  }

  // Get num of switch device support
  else if (command == GET_NUM_SWITCH)
  {
    _serial.println(TOTAL_SWT);
  }
  
  // Get max settings device support
  else if (command == GET_MAX_SETTINGS)
  {
    _serial.println(MAX_SETTINGS);
  }
  
  // Read value from EEPROM
  else if (command == GET_ROM_VAL && (val_i >= 0 && val_i <= MAX_ROM_VAL))
  {
    _serial.println(getROMvalue(byte(val_i)));
  }

  // Write value to EEPROM
  else if (command >= 0 && command <= MAX_ROM_VAL && val_i >= 0 && val_i < MAX_ROM_VAL)
  {
    setROMvalue(command, byte(val_i));
    delay(50);
    _serial.println(getROMvalue(byte(command)));
  }
  else {
    _serial.println(-1);
  }
}

void runSerialMode()
{
  while (!_serial.available());
  
  while(_serial.available())
  {
    char buff[CHAR_LEN];
    uint8_t x = _serial.readBytes(buff, CHAR_LEN - 1);
    buff[x] = '\0';

    char* token = strtok(buff, ":");
    uint8_t _command = atoi(token);
    token = strtok(NULL, ":");

    if (_command > 0 && token != NULL) {
      executeCommand(_command, token);
    }
  }
}
