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
	/* Serial.print("State: "); */
	/* Serial.print(state); */
	/* Serial.print(" Secs: "); */
	/* Serial.print(secs); */
	/* Serial.print("  Onsecs: "); */
	/* Serial.print(ON_SECS); */
	/* Serial.print("  Offsecs: "); */
	/* Serial.println(OFF_SECS); */
	char tmp[900];
	snprintf(tmp, 900,
		"<!DOCTYPE html><html><head><title>Motor Relay Cycling...</title>"
		"<meta charset='UTF-8' /><style type='text/css'>"
		".st{float:left;color:white;}"
		".on_sty  {background:#00a000;}"
		".bar_sty {background:#a00000; color:white; width:99%%; }"
		".bar_sty td {padding:2px 0 2px 1em; }"
		".cur_sty {width:99%%; }"
		".bar     {background:black; color:white;}"
		"</style>"
		"</head><body>"
		"<div>State: %s</div>"
		"<div>Ontime: %ds, Off-time: %ds, Total-time: %ds</div>"
		"<div>Current seconds: %d</div>"
		"<table class=bar_sty><tr>"
		//          \/ ON_SECS percentage
 		"<td width='%d%%' class=on_sty>ON</td><td>OFF</td></tr></table>"
		"<table class=cur_sty><tr>"
		//          \/ cur_secs percentage
 		"<td width='%d%%'>&nbsp;</td>"
 		"<td width='1%%' class=bar>↑</td><td>&nbsp;</td></tr></table>"

		"</body>"
		"</html>",
			str_curstate(),
			ON_SECS, OFF_SECS, ON_SECS+OFF_SECS,
			secs,
			max(1,(int)(ON_SECS*100)/(ON_SECS+OFF_SECS)),
			max(1,(int)(secs*100)/(ON_SECS+OFF_SECS))
		);
	server.send(200, "text/html", tmp);
}

