const int relayPin = 5; // 5 is D1Mini's D1
                        // HIGH is relay on.
const long interval = 1000;  // pause for two seconds
unsigned long currentTime;
unsigned long loopTime;
const int ledPin = LED_BUILTIN;
unsigned int state = 0;
unsigned long secs = 0;
unsigned long mins = 0;

void setup() {
	Serial.begin(9600);
	pinMode(relayPin, OUTPUT);
	digitalWrite(relayPin, HIGH);  // turn off relay
	pinMode(relayPin, OUTPUT);
	pinMode(ledPin, OUTPUT);
	currentTime = millis();
	loopTime = currentTime;
}

#define ON_SECS       10
#define OFF_SECS      30 
//#define LONGREST_SECS (20)
#define STATE_ON       0
#define STATE_OFF      1
#define STATE_LONGREST 2
void loop() {
	currentTime = millis();
	if ((currentTime-loopTime) > 1000) {
		secs++;
		loopTime = currentTime;
	}
	if (secs >= 60) {
		mins++;      // not using minutes currently though
		secs = 0;
	}
	if (secs < ON_SECS) {  // Testing with seconds for now
 	  		               //  but later will be minutes.
      					   // This should be off for 3 secs,
      					   //  then on for 5 more secs
      					   // (ie. until 8 seconds total have
      					   //  passed)
		if (state != STATE_ON) {
			digitalWrite(relayPin, HIGH);
			state = 0;
		}
	} else if (secs < ON_SECS+OFF_SECS) {
		if (state != STATE_OFF) {
			digitalWrite(relayPin, LOW);
			state = 1;
		}
	} else {
		secs = 0;
		mins = 0;
	}
}
