#include "framework.hpp"
#include <Ticker.h>

/* declare int for storing led number */
int example_led_indicator;

// Подготовительный процесс перед обновлением прошивки, например отключение реле и т.д. Обязательная функция, может быть пустой.
void user_update_prepare() {
  ;
}

// Функция вызывается когда получает сообщение от сервера. Обязательная функция
bool process_command(JsonDocument command) {
  Serial.println("COMMAND PROCESSING");
  JsonArray button = command["command"]["button"];
  for (JsonVariant item : button) {
    String current_button = item.as<String>();
    Serial.println(String(F("Pressed button: ")) + current_button);
    if (current_button == "example_button") {
      Serial.println("Do somenthing on button press...");
    }
  }

  JsonObject number = command["command"]["number"];
  for (JsonPair kv : number) {
    String current_number_name = kv.key().c_str();
    int current_number_value = kv.value().as<int>();
    Serial.println(String(F("Received data for number: ")) + current_number_name + String(F(" = ")) + String(current_number_value));
    device_status["number"][current_number_name] = current_number_value;
  }

  JsonObject ha_switch = command["command"]["switch"];
  for (JsonPair kv : ha_switch) {
    String current_switch_name = kv.key().c_str();
    bool current_switch_value = kv.value().as<bool>();
    Serial.println(String(F("Received data for switch: ")) + current_switch_name + String(F(" -> ")) + String(current_switch_value));
    device_status["switch"][current_switch_name] = current_switch_value;
    if (current_switch_name == "example_switch") {
      Serial.println("Do somenthing on switch change...");
      if(current_switch_value) LEDON(example_led_indicator);
      else LEDOFF(example_led_indicator);
    }
  }

  return true;
}




void setup() {
  framework_setup();

  FIRMWARE_VERSION = 2;
  START_AP_PIN = 5;
  DEVICE_TYPE = "example";

  /* User settings */

  /* initializing led for use */
  example_led_indicator = addLED(8);

  /* Adding binary_sensor for HA integration */
  JsonObject binary_sensor = device_status.createNestedObject("binary_sensor");
  binary_sensor["example_binary_sensor"] = false;

  /* Adding number for HA integration*/
  JsonObject number = device_status.createNestedObject("number");
  number["example_number"] = 10;

  /* Adding button for HA integration */
  device_status["button"].add("example_button");

  /* Adding switch for HA integration */
  JsonObject ha_switch = device_status.createNestedObject("switch");
  ha_switch["example_switch"] = false;
}

void loop() {
  framework_loop();
  /* User main loop */
  
}
