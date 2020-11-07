#define NUM_PINS_ADDR 0

void initVarsFromRom()
{
  byte vs = EEPROM.read(NUM_PINS_ADDR);

  if (vs == TOTAL_SWT) {
    byte cnt = 1;
    for (byte r = 0; r < MAX_SETTINGS; r++)
    {
      for (byte c = 0; c <= 2; c++) // 0=Pin, 1=On, 2=Off
      {
        Switches[r][c] = EEPROM.read(cnt);
        cnt++;
      }
    }
  }
  else {
    // First time
    EEPROM.write(NUM_PINS_ADDR, TOTAL_SWT);

    byte cnt = 1;
    for (byte r = 0; r < MAX_SETTINGS; r++)
    {
      for (byte c = 0; c <= 2; c++) // 0=Pin, 1=On, 2=Off
      {
        EEPROM.write(cnt, Switches[r][c]);
        cnt++;
      }
    }
  }
}

byte getROMvalue(byte addr)
{
  return EEPROM.read(addr);
}

void setROMvalue(byte addr, byte val)
{
  EEPROM.update(addr, val);
}

void clearEEPROM()
{
  for (byte i = 0; i < EEPROM.length(); i++)
  {
    EEPROM.write(i, 0);
  }
}
