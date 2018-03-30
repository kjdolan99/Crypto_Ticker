# Crypto Ticker

This program will display current cryptocurrency prices on a small display. Price information is acquired from cryptocompare.com over WiFi or bluetooth. The board is based around the ESP32 microcontroller, which integrates WiFi, Bluetooth, and BLE connectivity. The final product incorporates a 3D-printed case, lithium battery, touch button, OLED display, and main control board. The device is woken up with the touch button and subsequent presses will cycle through different currencies on the display.

## Getting Started

These instructions will get you a copy of the project up and running on your local machine for development and testing purposes. See deployment for notes on how to deploy the project on a live system.

### Prerequisites

The required software packages are available the main 3 operating systems.

* Install Arduino IDE
* Install  the [ESP32 SDK](https://learn.sparkfun.com/tutorials/esp32-thing-hookup-guide/installing-the-esp32-arduino-core) for Arduino

### Dependencies 

* [SSD1306 Driver](https://github.com/ThingPulse/esp8266-oled-ssd1306)
* [ArduinoJson](https://github.com/bblanchon/ArduinoJson.git)

* Clone to the "Home/Arduino/libraries" directory.

### Installing

A step by step series of examples that tell you have to get a development env running

Say what the step will be

```
Give the example
```

And repeat

```
until finished
```

End with an example of getting some data out of the system or using it for a little demo

## Running the tests

Explain how to run the automated tests for this system

### Break down into end to end tests

Explain what these tests test and why

```
Give an example
```

### Issues

* Uploading code to some boards sometimes fails. Change the serial upload speed from 921600 to 115200

## Deployment

Add additional notes about how to deploy this on a live system

## Built With

* Arduino IDE
* Espressif SDK

## Contributing

* Kevin Dolan (kjdolan999@gmail.com)

## Versioning

## Authors

* **Kevin Dolan** - *Initial work* - [kjdolan99](https://github.com/kjdolan99)

## License

This project is licensed under the MIT License - see the [LICENSE.md](LICENSE.md) file for details

## Acknowledgments

* https://techtutorialsx.com/
* Andreas Spiess
* Hat tip to anyone who's code was used
* Inspiration
* etc

