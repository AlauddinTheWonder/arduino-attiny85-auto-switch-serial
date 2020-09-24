Arduino ATtiny85 Switch 
=======================
> 3 pin with Serial (UART) Device control


Simple low powered automation to switch 3 AC sockets and controlled by Serial Device. #ATtiny85


## Devices required
1. ATtiny85
2. DS1307 or DS3231 RTC module
3. HC-05 or HM-10 Bluetooth module
4. 5v power supply


## ATtiny85 pins:


Pin   | Name         | Wire connection
----- | ------------ | ---------------
1     | Reset        | Not connected              
2     | I/O Pin 3    | Switch 2, UART: Tx         
3     | I/O Pin 4    | Switch 3, UART: Rx         
4     | GND          | Connected to Ground        
5     | I/O Pin 0    | RTC SDA                    
6     | I/O Pin 1    | Switch 1, Mode change pin
7     | I/O Pin 2    | RTC SCL                    
8     | VCC          | Connected to +3.3v to +5v  


> **Note**: Mode pin should be connected to `GND` via `10K` resistor. 
> To enable configuration mode, connect the Mode pin to `VCC` and need to restart the device.


## Configuration Mode

To access device from UART Device, start device in Config mode by connecting MODE pin with VCC.

For commands, have to send two bytes with 50ms gap.
```
-> First byte will be COMMAND
-> Second byte will be PARAMS (Values)
```

Command details:

Sr No  | Command  | Param      | Return      | Description
------ | -------- | -----------| ----------- | -----------
1      | 255      | 0          | 255         | Pingback. To recognize this device
2      | 254      | 0          | TIMESTAMP   | Get RTC time in timestamp (UTC)
3      | 253      | TIMESTAMP  | SAME_PARAM  | Set RTC time, value in timestampt (UTC). Return the same as Param if success
4      | 252      | 0          | 1-30        | Get number of switch device support. Ex. 3
5      | 251      | ROM_ADDR   | 0-255       | Read value from EEPROM. To read switch value. ROM_ADDR will be between 0 and (PIN_COUNT * 2)
6      | 251      | 250        | 0-59        | Get time drift in second(s)
7      | 250      | 0-59       | SAME_PARAM  | Set time drift in second(s)
8      | 0-60     | 0-23       | SAME_PARAM  | Write value to EEPROM. Set hours to switches.


> To update Switch on-off hour:

Switch    | Command | Param
--------- | ------- | ------
Swt 1 On  | 0       | 0-23
Swt 1 Off | 1       | 0-23
Swt 2 On  | 2       | 0-23
Swt 2 Off | 3       | 0-23
Swt 3 On  | 4       | 0-23
Swt 3 Off | 5       | 0-23
so on...  |         |     


---
  
Best Regards,  
Alauddin Ansari 
([GitHub Page](https://github.com/AlauddinTheWonder "Alauddin Ansari"))
