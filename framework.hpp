/* 
VERSION 1.2 (2024-11-28)
*/
#pragma once
#include <Arduino.h>
#include <ArduinoJson.h>
#include <WiFi.h>
#include <WiFiClient.h>
#include <WebServer.h>
#include <DNSServer.h>
#include <EEPROM.h>
#include "Hash.h"
#include <WebSocketsClient.h>
#include <time.h>
#include <HTTPClient.h>
#include <WiFiClientSecure.h>
#include <HTTPUpdate.h>
#include <time.h>
#include <Ticker.h>


/* Section of system_info settings, may be overwritten in user sketch */
int FIRMWARE_VERSION = 1;
String DEVICE_TYPE = "default";
/* Section of default settings, may be overwritten in user sketch */
int WiFi_STATUS_LED_PIN = 21;
int WS_STATUS_LED_PIN = 20;
int START_AP_PIN = 5;
String AP_PASSWORD = "12345678";

bool process_command(JsonDocument);
void user_update_prepare();

int WiFi_STATUS_LED = 0, WS_STATUS_LED = 0;
int addLED(int);
void LEDOFF(int);
void LEDON(int);
void LEDBLINK(int);
void LEDBLINKFAST(int);

/*
 lets-encrypt ISRG Root X1 certificate
*/
const char *rootCACertificate =
  "-----BEGIN CERTIFICATE-----\n"
  "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\n"
  "-----END CERTIFICATE-----\n";

/* WIFI credentials, mustn't be set manually, loading from EEPROM */
char ssid[33] = "";
char password[65] = "";
DNSServer dnsServer;
WebServer server(80);
WebSocketsClient webSocket;
/* Soft AP network parameters */
IPAddress apIP(172, 217, 28, 1);
IPAddress netMsk(255, 255, 255, 0);
/* Should I connect to WLAN asap? */
bool connect;
/* WiFi connected? */
bool connected = false;
/* WebSocket connected? */
bool ws_connected = false;
/* WebSocket authenticated? */
bool ws_authenticated = false;
/* UUID of request, need for correct server response? */
String ws_request_uuid = "";
/* Start time, when controller got NTP time.? */
struct tm startTime;
/** Last time I tried to connect to WLAN */
unsigned long lastConnectTry = 0;
/** Current WLAN status */
unsigned int wifi_status = WL_IDLE_STATUS;

String unique_id = "";  // sha1(String(WiFi.macAddress()) + ssid + password);
String token = sha1(String(WiFi.macAddress()));
String hostname = String(F("ESP32-")) + WiFi.macAddress();

// JSON with device status. Can be edited on every part of project and send after it.
JsonDocument device_status;

/* Start AP functional */
volatile bool startAP = false;

void ap_start_pressed() {
  startAP = true;
}


Ticker timer;
int ledTact = 0;
uint8_t ledNumber = 0;
#define MAX_LED 10
int ledStatus[MAX_LED]; // 0 - off, 1 - on, 2 - blink, 3 - blink fast
int ledPin[MAX_LED];

void onTimer(){

  for(uint8_t led = 0; led < ledNumber; led++){ // process leds
    if(ledStatus[led] == 0) digitalWrite(ledPin[led], LOW); // OFF
    else if(ledStatus[led] == 1) digitalWrite(ledPin[led], HIGH); // ON
    else if(ledStatus[led] == 2) {
      if(ledTact < 2) digitalWrite(ledPin[led], HIGH); // ON
      else digitalWrite(ledPin[led], LOW); // OFF
    }
    else if(ledStatus[led] == 3) {
      if(ledTact == 0 || ledTact == 2) digitalWrite(ledPin[led], HIGH); // ON
      else digitalWrite(ledPin[led], LOW); // OFF
    }
  }
  ledTact++;
  if(ledTact >= 4) ledTact = 0;
}

int addLED(int led_pin){
  if (ledNumber >= MAX_LED) return -1;
  ledPin[ledNumber] = led_pin;
  ledStatus[ledNumber] = 0;
  pinMode(led_pin, OUTPUT);
  digitalWrite(led_pin, LOW);
  ledNumber += 1;
  
  return ledNumber;
}

void LEDON(int led_num){
  if (led_num > ledNumber || led_num < 1) return;
  ledStatus[led_num - 1] = 1;
}

void LEDOFF(int led_num){
  if (led_num > ledNumber || led_num < 1) return;
  ledStatus[led_num - 1] = 0;
}

void LEDBLINK(int led_num){
  if (led_num > ledNumber || led_num < 1) return;
  ledStatus[led_num - 1] = 2;
}

void LEDBLINKFAST(int led_num){
  if (led_num > ledNumber || led_num < 1) return;
  ledStatus[led_num - 1] = 3;
}



/** Load WLAN credentials from EEPROM */
void loadCredentials() {
  EEPROM.begin(512);
  EEPROM.get(0, ssid);
  EEPROM.get(0 + sizeof(ssid), password);
  char ok[2 + 1];
  EEPROM.get(0 + sizeof(ssid) + sizeof(password), ok);
  EEPROM.end();
  if (String(ok) != String("OK")) {
    ssid[0] = 0;
    password[0] = 0;
  }
  Serial.println("Recovered credentials:");
  Serial.println(ssid);
  Serial.println(strlen(password) > 0 ? "********" : "<no password>");
}

/** Store WLAN credentials to EEPROM */
void saveCredentials() {
  EEPROM.begin(512);
  EEPROM.put(0, ssid);
  EEPROM.put(0 + sizeof(ssid), password);
  char ok[2 + 1] = "OK";
  EEPROM.put(0 + sizeof(ssid) + sizeof(password), ok);
  EEPROM.commit();
  EEPROM.end();
}

/** Reset WLAN credentials to EEPROM */
void resetCredentials() {
  EEPROM.begin(512);
  for (int i = 0; i < 512; i++) EEPROM.put(i, 0);
  EEPROM.commit();
  EEPROM.end();
}

/** Is this an IP? */
boolean isIp(String str) {
  for (size_t i = 0; i < str.length(); i++) {
    int c = str.charAt(i);
    if (c != '.' && (c < '0' || c > '9')) { return false; }
  }
  return true;
}

/** IP to String? */
String toStringIp(IPAddress ip) {
  String res = "";
  for (int i = 0; i < 3; i++) { res += String((ip >> (8 * i)) & 0xFF) + "."; }
  res += String(((ip >> 8 * 3)) & 0xFF);
  return res;
}

/** Wifi config page handler */
void handleWifi() {
  server.sendHeader("Cache-Control", "no-cache, no-store, must-revalidate");
  server.sendHeader("Pragma", "no-cache");
  server.sendHeader("Expires", "-1");

  String Page;
  Page += F("<!DOCTYPE html><html lang='en'><head>"
            "<meta name='viewport' content='width=device-width'>"
            "<title>CaptivePortal</title></head><body>"
            "<h1>Wifi config</h1>");
  Page += String(F("<br>MAC: ")) + WiFi.macAddress() + F("<br>");
  Page += String(F("<br>Hostname: ")) + WiFi.getHostname() + F("<br>");
  Page += String(F("<br>IP: ")) + toStringIp(WiFi.localIP()) + F("<br>");
  Page += String(F("<br>Gateway: ")) + toStringIp(WiFi.gatewayIP()) + F(", DNS: ") + toStringIp(WiFi.dnsIP()) + F("<br>");
  Page += String(F("<br>ID: ")) + unique_id + F("<br>Token: ") + token + F("<br>");

  Page += String(F("\r\n<br /><table><tr><th align='left'>WLAN config</th></tr><tr><td>SSID: "))
          + String(ssid) + F(" / ") + String(password) + F("</td></tr>")
          + F("</table>\r\n<br />");
  Page += F("\r\n<br /><form method='POST' action='wifisave'><h4>Connect to network:</h4>"
            "<input type='text' placeholder='network' name='n'/>"
            "<br /><input type='password' placeholder='password' name='p'/>"
            "<br /><input type='submit' value='Connect/Disconnect'/></form>"
            "</body></html>");
  server.send(200, "text/html", Page);
  server.client().stop();  // Stop is needed because we sent no content length`
}

/** Handle the WLAN save form and redirect to WLAN config page again */
void handleWifiSave() {
  Serial.println("wifi save");
  server.arg("n").toCharArray(ssid, sizeof(ssid) - 1);
  server.arg("p").toCharArray(password, sizeof(password) - 1);
  server.sendHeader("Location", "wifi", true);
  server.sendHeader("Cache-Control", "no-cache, no-store, must-revalidate");
  server.sendHeader("Pragma", "no-cache");
  server.sendHeader("Expires", "-1");
  server.send(302, "text/plain", "");  // Empty content inhibits Content-length header so we have to close the socket ourselves.
  server.client().stop();              // Stop is needed because we sent no content length
  saveCredentials();
  connect = strlen(ssid) > 0;  // Request WLAN connect with new credentials if there is a SSID
}


void setClock() {
  configTime(0, 0, "pool.ntp.org", "time.nist.gov");  // UTC

  Serial.print(F("Waiting for NTP time sync: "));
  time_t now = time(nullptr);
  while (now < 8 * 3600 * 2) {
    yield();
    delay(500);
    Serial.print(F("."));
    now = time(nullptr);
  }

  Serial.println(F(""));
  struct tm timeinfo;
  gmtime_r(&now, &timeinfo);
  // Задаём время старта работы
  gmtime_r(&now, &startTime);
  Serial.print(F("Current time: "));
  Serial.print(asctime(&timeinfo));
  device_status["time_start"] = asctime(&startTime);
}

void updateFirmware() {
  user_update_prepare();
  Serial.printf("Start updating...\n");
  WiFiClientSecure client;
  client.setCACert(rootCACertificate);
  // Reading data over SSL may be slow, use an adequate timeout
  client.setTimeout(12000 / 1000);  // timeout argument is defined in seconds for setTimeout
  t_httpUpdate_return ret = httpUpdate.update(client, "relay.smarthome-tech.ru", 443, "/api/firmware/" + unique_id + "/" + token);
  switch (ret) {
    case HTTP_UPDATE_FAILED:
      Serial.printf("HTTP_UPDATE_FAILED Error (%d): %s\n", httpUpdate.getLastError(), httpUpdate.getLastErrorString().c_str());
      break;

    case HTTP_UPDATE_NO_UPDATES:
      Serial.println("HTTP_UPDATE_NO_UPDATES");
      break;

    case HTTP_UPDATE_OK:
      Serial.println("HTTP_UPDATE_OK");
      break;
  }
}




void webSocketSendStatus() {
  JsonDocument doc;
  doc["uuid"] = ws_request_uuid;
  doc["status"] = device_status;
  String status_json = "";
  serializeJson(doc, status_json);
  webSocket.sendTXT(status_json);
}

void webSocketSendSystemInfo() {
  JsonDocument doc;
  doc["uuid"] = ws_request_uuid;


  JsonObject system_info = doc.createNestedObject("system_info");
  system_info["ip"] = toStringIp(WiFi.localIP());
  system_info["mac"] = WiFi.macAddress();
  system_info["gw"] = toStringIp(WiFi.gatewayIP());
  system_info["dns"] = toStringIp(WiFi.dnsIP());
  system_info["ssid"] = ssid;
  system_info["device_type"] = DEVICE_TYPE;
  system_info["fw_version"] = FIRMWARE_VERSION;
  time_t now = time(nullptr);
  struct tm timeinfo;
  gmtime_r(&now, &timeinfo);
  system_info["time"] = asctime(&timeinfo);
  String json = "";
  serializeJson(doc, json);
  webSocket.sendTXT(json);
}

void webSocketEvent(WStype_t type, uint8_t *payload, size_t length) {

  switch (type) {
    case WStype_DISCONNECTED:
      Serial.printf("[WSc] Disconnected!\n");
      ws_connected = false;
      ws_authenticated = false;
      LEDBLINKFAST(WS_STATUS_LED);
      break;
    case WStype_CONNECTED:
      {
        Serial.printf("[WSc] Connected to url: %s\n", payload);
        ws_connected = true;
        LEDON(WS_STATUS_LED);
        // send message to server when Connected
        Serial.println("[WSc] SENDING AUTH JSON");
        JsonDocument auth_json;
        auth_json["id"] = unique_id;
        auth_json["token"] = token;
        String json = "";
        serializeJson(auth_json, json);
        webSocket.sendTXT(json);
      }
      break;
    case WStype_TEXT:
      {
        Serial.printf("[WSc] RESPONSE: %s\n", payload);
        JsonDocument response_json;
        DeserializationError response_error = deserializeJson(response_json, payload);
        if (!response_error) {
          if (response_json["uuid"] != nullptr) {
            String temp = response_json["uuid"];
            ws_request_uuid = temp;
          } else {
            ws_request_uuid = "";
          }

          if (response_json["info"] != nullptr) {  // Обрабатываем блок info
            String info = response_json["info"];
            Serial.println("info");
            if (info == "authorized") {
              Serial.println("authorized");
              ws_authenticated = true;
            }
          }
          if (response_json["request"] != nullptr) {  // Обрабатываем блок req
            String request = response_json["request"];
            Serial.println("request");
            if (request == "system_info") {  // Отправляем инфо о системе
              Serial.println("system_info");
              webSocketSendSystemInfo();
            } else if (request == "status") {  // Отправляем инфо о системе
              Serial.println("status");
              webSocketSendStatus();
            }
          }
          if (response_json["command"] != nullptr) {  // Обрабатываем блок command
            JsonDocument doc;
            doc["uuid"] = ws_request_uuid;
            doc["command"] = true;
            String json = "";
            serializeJson(doc, json);
            webSocket.sendTXT(json);
            process_command(response_json);
          }
          if (response_json["fw"] != nullptr && response_json["fw"]["ver"] != nullptr) {  // Обрабатываем блок fw
            unsigned int available_version = response_json["fw"]["ver"];
            Serial.printf("available_version: %d, current_version: %d\n", available_version, FIRMWARE_VERSION);
            if (available_version > FIRMWARE_VERSION) updateFirmware();
          }
        }
      }
      break;
    case WStype_BIN:
      break;
    case WStype_PING:
      // pong will be send automatically
      Serial.printf("[WSc] get ping\n");
      break;
    case WStype_PONG:
      // answer to a ping we send
      Serial.printf("[WSc] get pong\n");
      break;
    case WStype_ERROR:
    case WStype_FRAGMENT_TEXT_START:
    case WStype_FRAGMENT_BIN_START:
    case WStype_FRAGMENT:
    case WStype_FRAGMENT_FIN:
      break;
  }
}


void start_ap() {
  Serial.println("Configuring access point...");
  /* You can remove the password parameter if you want the AP to be open. */
  WiFi.softAPConfig(apIP, apIP, netMsk);
  WiFi.softAP(hostname, AP_PASSWORD);
  delay(500);  // Without delay I've seen the IP address blank
  Serial.print("AP IP address: ");
  Serial.println(WiFi.softAPIP());
  /* Setup the DNS server redirecting all the domains to the apIP */
  dnsServer.setErrorReplyCode(DNSReplyCode::NoError);
  dnsServer.start(53, "*", apIP);

  /* Setup web pages: root, wifi config pages, SO captive portal detectors and not found. */
  // server.on("/", handleWifi);
  // server.on("/wifi", handleWifi);
  server.on("/wifisave", handleWifiSave);
  server.onNotFound(handleWifi);
  server.begin();  // Web server start
  Serial.println("HTTP server started");
}



void connectWifi() {
  Serial.println("Connecting as wifi client...");
  WiFi.disconnect();
  WiFi.begin(ssid, password);
  int connRes = WiFi.waitForConnectResult();
  Serial.print("connRes: ");
  Serial.println(connRes);
}

void framework_setup() {

  /* Credentials reset functional */
  pinMode(START_AP_PIN, INPUT_PULLDOWN);
  attachInterrupt(START_AP_PIN, ap_start_pressed, FALLING);
  /* Credentials reset functional */
  delay(1000);
  Serial.begin(115200);
  Serial.println();
  loadCredentials();           // Load WLAN credentials from network
  connect = strlen(ssid) > 0;  // Request WLAN connect if there is a SSID
  // server address, port and URL
  webSocket.beginSslWithCA("relay.smarthome-tech.ru", 443, "/ws/device/v1", rootCACertificate);
  // event handler
  webSocket.onEvent(webSocketEvent);

  timer.attach(0.25, onTimer);

  WiFi_STATUS_LED = addLED(WiFi_STATUS_LED_PIN);
  WS_STATUS_LED = addLED(WS_STATUS_LED_PIN);
}

void framework_loop() {
  if (startAP) {
    Serial.println("Start AP requested.");
    start_ap();
    startAP = false;
  }

  if (connect) {
    Serial.println("Connect requested");
    connect = false;
    LEDBLINK(WiFi_STATUS_LED);
    connectWifi();
    lastConnectTry = millis();
  }
  {
    unsigned int s = WiFi.status();
    if (s == 0 && millis() > (lastConnectTry + 30000)) {
      /* If WLAN disconnected and idle try to connect */
      /* Don't set retry time too low as retry interfere the softAP operation */
      connect = true;
    }
    if (wifi_status != s) {  // WLAN status change
      Serial.print("Status: ");
      Serial.println(s);
      wifi_status = s;
      if (s == WL_CONNECTED) {
        /* Just connected to WLAN */
        Serial.println("");
        Serial.print("Connected to ");
        Serial.println(ssid);
        Serial.print("IP address: ");
        Serial.println(WiFi.localIP());
        unique_id = sha1(String(WiFi.macAddress()) + ssid + password);
        setClock();
        connected = true;
        LEDON(WiFi_STATUS_LED);
      } else if (s == WL_NO_SSID_AVAIL || s == WL_CONNECT_FAILED || s == WL_CONNECTION_LOST || s == WL_IDLE_STATUS) {
        WiFi.disconnect();
        LEDBLINKFAST(WiFi_STATUS_LED);
        LEDOFF(WS_STATUS_LED);
        connect = true;
        connected = false;
      }
    }
  }


  dnsServer.processNextRequest();
  server.handleClient();

  if (connected) webSocket.loop();
}