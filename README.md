# Crypto Ticker

This program will display current cryptocurrency prices on a small display. Price information is acquired from cryptocompare.com over WiFi or bluetooth. The board is based around the ESP32 microcontroller, which integrates WiFi, Bluetooth, and BLE connectivity. The final product incorporates a 3D-printed case, lithium battery, touch button, OLED display, and main control board. The device is woken up with the touch button and subsequent presses will cycle through different currencies on the display.

## Getting Started


### Hardware

* [Pro ESP32 OLED V2.0 TTGO](https://www.aliexpress.com/item/Lolin-ESP32-OLED-V2-0-Pro-ESP32-OLED-wemos-pour-Arduino-ESP32-OLED-WiFi-Modules-Bluetooth/32824819112.html)
* [Capacitive Touch Button](https://www.aliexpress.com/item/10-Pcs-TTP223-Touch-Key-Switch-Module-Touching-Button-Capacitive-Switches-Self-Locking-No-Locking-Module/32793578915.html)
* Lithium Battery 6.0x24x47mm (602447)
* 3D printed case
* Hardware build instructions on [Instructables](https://www.instructables.com/id/Crypto-Ticker/)

### Prerequisites

The required software packages are available for the main 3 operating systems.

* Install the [Arduino IDE](https://www.arduino.cc/en/Main/Software)
* Install  the [ESP32 SDK](https://learn.sparkfun.com/tutorials/esp32-thing-hookup-guide/installing-the-esp32-arduino-core) for Arduino

### Dependencies 

* [SSD1306 Screen Driver](https://github.com/ThingPulse/esp8266-oled-ssd1306)
* [ArduinoJson](https://github.com/bblanchon/ArduinoJson)

* Clone to the "Home/Arduino/libraries" directory.

### Issues

* Uploading code to some boards fails. Change the serial upload speed from 921600 to 115200 in the Arduino IDE.

## Built With

* Arduino IDE
* Espressif SDK

## Contributing

## Authors

* **Kevin Dolan** - *Initial work* - [kjdolan99](https://github.com/kjdolan99)

## License

This project is licensed under the MIT License - see the [LICENSE.md](LICENSE.md) file for details

## Acknowledgments

* https://techtutorialsx.com/
* Andreas Spiess
* Daniel Eichhorn [(@squix78)](https://github.com/squix78)


