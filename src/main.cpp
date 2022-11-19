#include <Arduino.h>
#include <Network/NetworkManager.h>

/*
  Steps to setup a new ESP32:
  1. Upload the content of the data dir to SPIFFS
    -> see https://randomnerdtutorials.com/esp32-vs-code-platformio-spiffs/
  2. Set the correct COM Port in platformio.ini
    -> Quick Access -> PIO Home -> Devices lists all connected devices and COM ports
  3. Build and Upload this project
  4. Use smartphone and list all network devices
    -> connect to your device (ESP32-XXXXXXX) and open 192.168.4.1 via browser
  5. Set Wifi credentials and submit. The ESP32 will reboot.
  6. Go to platformio.ini and uncomment these lines to enable OTA uploads:
    -> upload_protocol
    -> extra_scripts
    -> upload_url (make sure you set the correct WIFI IP of your ESP32 here)
  7. You can access the netsettings of your ESP32 under the given WIFI IP again and change settings

*/

NetworkManager networkManager;

void setup()
{
  Serial.begin(115200);
  delay(5000);

  networkManager.begin();
}

void loop()
{
  networkManager.loop();
}
