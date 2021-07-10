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
	server.send(200, "text/plain", "k\n");
	relay_reset_timer();
}

void http_sleep() {
	server.send(200, "text/plain", "k\n");
	relay_jump_to_sleep_cycle();
}

void http_root() {
	server.send(200, "text/plain", "Hi\n");
}
