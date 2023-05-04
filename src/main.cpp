  //  Copyright 2023 Krzysztof Pochwała

  //  Licensed under the Apache License, Version 2.0 (the "License");
  //  you may not use this file except in compliance with the License.
  //  You may obtain a copy of the License at

  //     http://www.apache.org/licenses/LICENSE-2.0

  //  Unless required by applicable law or agreed to in writing, software
  //  distributed under the License is distributed on an "AS IS" BASIS,
  //  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  //  See the License for the specific language governing permissions and
  //  limitations under the License.

#include <Arduino.h>
#include <ESP32_Servo.h>
#include <WiFi.h>
#include <EasyLed.h>
#include <ESPTelnet.h>
#include <ezLED.h>
#include <Preferences.h>


// static constexpr auto pin = 40;
static constexpr auto left_pin = 15;
static constexpr auto right_pin = 16;

static char const SSID[] = "kabot";  /* your network SSID (name) */
static char const PASS[] = "kabot";  /* your network password (use for WPA, or use as key for WEP) */

Servo left;
Servo right;

EasyLed navigationLights(40, EasyLed::ActiveLevel::High, EasyLed::State::Off);
// EasyLed statusLed(41, EasyLed::ActiveLevel::High, EasyLed::State::Off);
ezLED statusLed(41);

ESPTelnet telnet;

void handleTelnet(void * parameter){

  for(;;){ // infinite loop

    telnet.loop();
    vTaskDelay(10 / portTICK_PERIOD_MS);
  }
}

void handleLed(void * parameter){

  bool isFadedIn = false;

  for(;;){ // infinite loop

    auto isConnected = WiFi.status() != WL_CONNECTED;

    auto fadeTime = isConnected ? 100 : 1000;

    if (statusLed.getState() == LED_IDLE) {
      if (isFadedIn == false) {
        statusLed.fade(0, 255, fadeTime);
        isFadedIn = true;
      } else {
        statusLed.fade(255, 0, fadeTime);
        isFadedIn = false;
      }
    }

    statusLed.loop();
    vTaskDelay(30 / portTICK_PERIOD_MS);
  }
}

void setup() {

  xTaskCreate(handleLed, "Handle statusLed", 1024*8, nullptr, 1, nullptr);

  Serial.begin(9600);
  Serial.setDebugOutput(true);
  telnet.begin();
  
  // while(!Serial);

  
  while (WiFi.status() != WL_CONNECTED)
  {
    Serial.print("Attempting to connect to '");
    Serial.print(SSID);
    Serial.println("'");
    WiFi.begin(SSID, PASS);
    delay(1000);
  }
  // statusLed.cancel();
  // statusLed.fade(0, 255, 500);

  Serial.print  ("You're connected to '");
  Serial.print  (WiFi.SSID());
  Serial.println("'");


  auto lok = left.attach(left_pin);
  auto rok = right.attach(right_pin);
  
  telnet.begin(23);
  delay(3000);
  Serial.println(WiFi.localIP());


  telnet.onConnect([](String ip){ navigationLights.on(); });
  telnet.onDisconnect([](String ip){ navigationLights.off(); });


  xTaskCreate(handleTelnet, "Handle telnet", 1024*8, nullptr, 1, nullptr);
}

void loop() {


  auto battery = analogRead(7) / 3400.0 * 4.2;
  telnet.printf("Battery level: %.2f \n", battery);
  delay(1000);

  // uint32_t chipId = 0;

	// for(int i=0; i<17; i=i+8) {
	//   chipId |= ((ESP.getEfuseMac() >> (40 - i)) & 0xff) << i;
	// }

  // Serial.print("Chip ID: "); Serial.println(chipId);
	// Serial.printf("ESP32 Chip model = %s Rev %d\n", ESP.getChipModel(), ESP.getChipRevision());
	// Serial.printf("This chip has %d cores\n", ESP.getChipCores());
  // Serial.printf("Psram size %d\n", ESP.getPsramSize());
  // Serial.println(WiFi.localIP());

  // delay(1000);

  // digitalWrite(pin, LOW);

  // left.write(10);
  // right.write(170);

  // delay(1000);

  // left.write(90);
  // right.write(90);

  // delay(1000);

  // digitalWrite(pin, HIGH);

  // left.write(170);
  // right.write(10);

  // delay(1000);

  // left.write(90);
  // right.write(90);

  // delay(1000);
}