# arduino_iot_relay_example

Needed libraries:
* ArduinoJson (https://arduinojson.org)
* ArduinoWebsockets (https://github.com/gilmaimon/ArduinoWebsockets)

This is an example of ESP32 device, connected to Home Assistant (https://github.com/nezvanovml/relay_homeassistant) using Relay (https://github.com/nezvanovml/Relay)

Steps:
1) Clone repository
2) Install libraries
3) Select your board, port
4) Upload code to your board
5) Make short impulse to +3.3v to START_AP_PIN, it will turn ON WiFi access point
6) Connect to WiFi named "ESP32-XX:XX:XX:XX:XX:XX", password 12345678
7) Your browser must open page for login, in this page enter your home WiFi SSID & password, then press "Connect"
8) Wait for connection...
9) Get ID & Token from page for future connection to device.
10) Don't forget to reset device to disable AP.
11) Open https://relay.smarthome-tech.ru/system_info and enter ID & Token, press "Find"
12) You can see your device info, also you can see status (https://relay.smarthome-tech.ru/status) and upload new firmware for OTA update (https://relay.smarthome-tech.ru/firmware)
