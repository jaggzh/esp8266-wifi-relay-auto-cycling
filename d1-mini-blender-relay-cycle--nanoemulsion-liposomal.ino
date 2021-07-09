#define __MAIN_INO__
#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
//#include <ESP8266HTTPUpdateServer.h>

#include "wifi_config.h" // This sets actual values (gross): ssid, password. ip, gw, nm
#include "printutils.h"
#include "ota.h"
#include "wifi.h"
#include "espweb.h"

/* #define ON_SECS       (10)  // vitamin c (bullet blender) */
/* #define OFF_SECS      (30) */
#define ON_SECS       (60*10)  // Nebulizer
#define OFF_SECS      (60*30)

//#define LONGREST_SECS (20)
#define STATE_ON       0
#define STATE_OFF      1
#define STATE_LONGREST 2

const int relayPin = 5; // 5 is D1Mini's D1
                        // HIGH is relay on.
const long interval = 1000;  // pause for two seconds
unsigned long cur_millis;
unsigned long lag_millis;
const int ledPin = LED_BUILTIN;
unsigned int state = 0;
unsigned long secs = 0;

void relay_reset_timer();
void relay_jump_to_sleep_cycle();

void relay_reset_timer() {
	// pause relay as a notice to the user
	digitalWrite(relayPin, HIGH);
	delay(2000);
	secs = 0;
	state = STATE_OFF; // say we're off so loop will turn us on
}

void relay_jump_to_sleep_cycle() {
	secs = ON_SECS;   // say we're at end of on-time
	state = STATE_ON; // say we're on so loop will force us off
}

void setup() {
	int tries=0;
	Serial.begin(115200);
	pinMode(relayPin, OUTPUT);
	digitalWrite(relayPin, LOW);  // make sure relay is off
	pinMode(ledPin, OUTPUT);
	digitalWrite(ledPin, LOW);
	setup_wifi();
	cur_millis = millis();
	lag_millis = cur_millis;
	setup_ota();
	while (WiFi.status() != WL_CONNECTED) {
		Serial.println("Not connected");
		delay(1000);
		if (tries++ > 20) {
			Serial.println("20 tries done. Giving up and seeing if we can move on.");
			break;
		}
	}
	//loop_check_wifi(cur_millis);
	setup_web();
}
void loop() {
	cur_millis = millis();
	loop_ota();
	if ((cur_millis-lag_millis) > 1000) {
		secs++;
		lag_millis = cur_millis;
	}
	/* Serial.print("State: "); */
	/* Serial.print(state); */
	/* Serial.print(" Secs: "); */
	/* Serial.print(secs); */
	/* Serial.print("  Onsecs: "); */
	/* Serial.print(ON_SECS); */
	/* Serial.print("  Offsecs: "); */
	/* Serial.println(OFF_SECS); */
	if (secs < ON_SECS) {  // Testing with seconds for now
      					   // This should be off for 3 secs,
      					   //  then on for 5 more secs
      					   // (ie. until 8 seconds total have
      					   //  passed)
		if (state != STATE_ON) {
			digitalWrite(relayPin, HIGH);
			state = STATE_ON;
		}
	} else if (secs < ON_SECS+OFF_SECS) {
		if (state != STATE_OFF) {
			digitalWrite(relayPin, LOW);
			state = STATE_OFF;
		}
	} else {
		secs = 0;
	}
}

void check_wifi() {
	static int connected=false;
	static int last_wifi_millis = lag_millis;
	if (lag_millis - last_wifi_millis > 3000) {
		last_wifi_millis = lag_millis;
		if (WiFi.status() == WL_CONNECTED) {
			if (!connected) { // only if we toggled state
				connected = true;
				sp(F("Just connected to "));
				sp(ssid);
				sp(". IP: ");
				spl(WiFi.localIP());
			}
		} else {
			if (!connected) {
				spl(F("Still not connected"));
			} else { // only if we toggled state
				connected=false;
				spl(F("Lost WiFi connection. Will try again."));
			}
		}
	}
}
