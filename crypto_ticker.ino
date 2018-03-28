/**
 * The MIT License (MIT)
 *
 * Copyright (c) 2016 by Daniel Eichhorn
 * Copyright (c) 2016 by Fabrice Weinberg
 * Modified by Kevin Dolan on 2018
 * Original File: SSD1306UiDemo.ino
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 *
 */
//Hardware: TTGO Pro ESP32 OLED V2.0 Board

#include "SSD1306.h" // alias for `#include "SSD1306Wire.h"`

// Include the UI lib
#include "OLEDDisplayUi.h"

// Include custom images
#include "images.h"

#include "ArduinoJson.h"

#include "WiFi.h"

#include "HTTPClient.h"

// WiFi Login Information
// Create a file called "WiFi_Login.h", copy the following, and fill in your login information
/*
const char* ssid = "WiFi_SSID";
//const char* password = "WiFi_PASSWORD";
*/
#include "WiFi_Login.h"

bool connected = false;

HTTPClient http;

WiFiClient client;

char server[] = "https://min-api.cryptocompare.com/data/price?fsym=BTC&tsyms=USD,ETH,LTC";

// Initialize the OLED display using Wire library
SSD1306  display(GEOMETRY_128_64, 0x3c, 4, 15);

OLEDDisplayUi ui     ( &display );

const size_t capacity = JSON_OBJECT_SIZE(3) + JSON_ARRAY_SIZE(2) + 60;
const	String cryptoCompare = "https://min-api.cryptocompare.com/data/";

class cryptoCoin{
	
	char * coin;
	String price;

	public:
	cryptoCoin(){
		coin = "NONE";
		price = "0.0";

	}	
	cryptoCoin(char * name){
		this->coin = name;
		updatePrice();
	}
  bool updatePrice(){

  String site = cryptoCompare + "price?fsym=" + this->coin + "&tsyms=USD,ETH,LTC";
  DynamicJsonBuffer jsonBuffer(capacity);

  http.begin(site);
  int httpCode = http.GET();

  if (httpCode > 0) { //Check for the returning code

        String payload = http.getString();
        Serial.println(httpCode);
        Serial.println(payload);

    // Parse JSON object
 	JsonObject& root = jsonBuffer.parseObject(payload);
	  if (!root.success()) {
	    Serial.println(F("Parsing failed!"));
	    return false;
		}	
	Serial.print(F("BTC: "));
	Serial.println(root["USD"].as<char*>());
	Serial.print(F("ETH: "));	
	Serial.println(root["ETH"].as<char*>());
    this->price = root["USD"].as<char*>();
    
     }

    else {
      Serial.println("Error on HTTP request");
      return false;
    }

    http.end(); //Free the resources   		  	
    return true;
	}
	String getPrice(){
		return this->price;
	}

};

void msOverlay(OLEDDisplay *display, OLEDDisplayUiState* state) {
  display->setTextAlignment(TEXT_ALIGN_RIGHT);
  display->setFont(ArialMT_Plain_10);
  display->drawString(128, 0, String(millis() / 1000));
}

void drawFrame1(OLEDDisplay *display, OLEDDisplayUiState* state, int16_t x, int16_t y) {

  display->setTextAlignment(TEXT_ALIGN_LEFT);
  display->setFont(ArialMT_Plain_16);
  display->drawString(0 + x, 16 + y, "Crypto Ticker!"); 	

}
cryptoCoin btc, eth;

void drawFrame2(OLEDDisplay *display, OLEDDisplayUiState* state, int16_t x, int16_t y) {
  display->setTextAlignment(TEXT_ALIGN_LEFT);
  display->setFont(ArialMT_Plain_16);
  display->drawString(0 + x, 10 + y,"BTC: $" + btc.getPrice());

}
void drawFrame3(OLEDDisplay *display, OLEDDisplayUiState* state, int16_t x, int16_t y) {
  display->setTextAlignment(TEXT_ALIGN_LEFT);
  display->setFont(ArialMT_Plain_16);
  display->drawString(0 + x, 10 + y,"ETH: " + eth.getPrice());

}

void drawFrame4(OLEDDisplay *display, OLEDDisplayUiState* state, int16_t x, int16_t y) {
  display->setTextAlignment(TEXT_ALIGN_LEFT);
  display->setFont(ArialMT_Plain_10);
  display->drawStringMaxWidth(0 + x, 10 + y, 128, "Connected to SSID: " + WiFi.SSID());
}

// void drawFrame5(OLEDDisplay *display, OLEDDisplayUiState* state, int16_t x, int16_t y) {}

// This array keeps function pointers to all frames
// frames are the single views that slide in
FrameCallback frames[] = { drawFrame1, drawFrame2, drawFrame3, drawFrame4};

// how many frames are there?
int frameCount = 4;

// Overlays are statically drawn on top of a frame eg. a clock
OverlayCallback overlays[] = { msOverlay };
int overlaysCount = 1;

void setup() {

	//Reset the OLED
  pinMode(16,OUTPUT);
  digitalWrite(16, LOW); // set GPIO16 low to reset OLED
  delay(50);
  digitalWrite(16, HIGH); // while OLED is running, must set GPIO16 in high

  //Initialize the serial terminal
  Serial.begin(115200);
  Serial.println();
  Serial.println();

  //Lower the FPS to reduce power?
  ui.setTargetFPS(60);

	// Customize the active and inactive symbol
  ui.setActiveSymbol(activeSymbol);
  ui.setInactiveSymbol(inactiveSymbol);

  // You can change this to
  // TOP, LEFT, BOTTOM, RIGHT
  ui.setIndicatorPosition(BOTTOM);
  
  // Defines where the first frame is located in the bar.
  ui.setIndicatorDirection(LEFT_RIGHT);

  // You can change the transition that is used
  // SLIDE_LEFT, SLIDE_RIGHT, SLIDE_UP, SLIDE_DOWN
  ui.setFrameAnimation(SLIDE_LEFT);

  // Add frames
  ui.setFrames(frames, frameCount);

  // Add overlays
  ui.setOverlays(overlays, overlaysCount);

  // Initialising the UI will init the display too.
  ui.init();

  display.flipScreenVertically();

  ui.setTimePerFrame(10000);

  //Create a new task to update the screen
  xTaskCreatePinnedToCore(
                    update_screen,   /* Function to implement the task */
                    "update_screen", /* Name of the task */
                    10000,      /* Stack size in words */
                    NULL,       /* Task input parameter */
                    1,          /* Priority of the task */
                    NULL,       /* Task handle. */
                    0);			/* Core number */

  // Connect to WiFi  
 WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi..");
  }
    Serial.println("Connected to SSID: " + WiFi.SSID());

    btc = cryptoCoin("BTC");
    btc.updatePrice();
    eth = cryptoCoin("ETH");
    eth.updatePrice();
   
}
int update = 0;

void loop() {
 
 // if(millis()- update > 10000){
  	  update = millis();
	  
	  btc.updatePrice();
	  eth.updatePrice();
	  ui.nextFrame();  	
  //}	
}
//Infinite loop to update the screen. Run as a task.
void update_screen(void* arg){

	while(true){
	int remainingTimeBudget = ui.update();

	  if (remainingTimeBudget > 0) {
	    // You can do some work here
	    // Don't do stuff if you are below your
	    // time budget.
	    delay(remainingTimeBudget);
    	}
	}
}

