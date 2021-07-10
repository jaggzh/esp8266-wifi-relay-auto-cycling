# Arduino ESP8266 Relay Control with basic WiFi API and OTA updates

I needed to control a medical device (a nebulizer compressor), cycling it on for 10 minutes, off for 30, to keep it from overheating.  I've also used this to cycle a Magic Bullet (tm) blender for preparing liposomal nanoemulsions.

## Notes:

* Make sure to install the ArduinoOTA library from the Arduino library manager. The ESP8266 OTA apparently does not work with the Arduino-packaged version.
* Ignore all the files in reference/ 
