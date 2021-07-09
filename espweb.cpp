#define __IN_ESPWEB_CPP
#include "espweb.h"

#include "main.h"

ESP8266WebServer server(80);

void setup_web() {
	server.on("/", http_root);
	server.on("/reset", http_reset);
	server.on("/sleep", http_sleep);
	server.begin();
}

void loop_web() {
	server.handleClient();
}

void http_reset() {
	relay_reset_timer();
	server.send(200, "text/plain", "k\n");
}

void http_sleep() {
	relay_jump_to_sleep_cycle();
	server.send(200, "text/plain", "k\n");
}

void http_root() {
	relay_jump_to_sleep_cycle();
	server.send(200, "text/plain", "Hi\n");
}
