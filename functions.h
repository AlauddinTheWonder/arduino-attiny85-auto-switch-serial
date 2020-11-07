/* 
 * Alauddin Ansari
 * 2018-11-20
 * General Functions
 */

uint8_t getOnOffStatus(uint8_t currentHour, uint8_t onTime, uint8_t offTime)
{
    if (onTime == offTime) {
        return 0;
    }

    if (onTime < offTime) {
        if (currentHour >= onTime && currentHour < offTime) {
            return 1;
        }
        return 0;
    }

    if (onTime > offTime) {
        if (currentHour >= onTime && currentHour <= 23) {
            return 1;
        }
        else if (currentHour < offTime) {
            return 1;
        }
        return 0;
    }
}

int8_t getIndexByPin(uint8_t arr[TOTAL_SWT], uint8_t pin)
{
  for (uint8_t i = 0; i < TOTAL_SWT; i++)
  {
    if (arr[i] == pin) {
      return i;
    }
  }
  return -1;
}
