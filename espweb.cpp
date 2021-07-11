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
	server.send(200, "text/html",
		"<html><head><title>On</title>"
		"<meta http-equiv=refresh content='2;url=/' /></head>"
		"<body>Turning ON<br></body></html>");
	relay_reset_timer();
}

void http_sleep() {
	server.send(200, "text/html",
		"<html><head><title>Off</title>"
		"<meta http-equiv=refresh content='2;url=/' /></head>"
		"<body>Turning OFF<br></body></html>");
	relay_jump_to_sleep_cycle();
}

int cycle_secs_left() {
	if (secs < ON_SECS) {
		return ON_SECS - secs;
	} else if (secs < ON_SECS + OFF_SECS) {
		return ON_SECS+OFF_SECS - secs;
	}
	return -1;
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
	int remsecs = cycle_secs_left();
	char tmp[941];
	float perc_on_cycle = ((float)ON_SECS*100)/((float)ON_SECS+OFF_SECS);
	float perc_now = ((float)secs*100)/((float)ON_SECS+OFF_SECS);
	snprintf(tmp, 1000,
		"<!DOCTYPE html><html><head><title>Motor Relay Cycling...</title>"
		"<meta charset=UTF-8 />"
		"<meta http-equiv=refresh content=20 />"
		"<style type=text/css>"
		".st{float:left;color:white;}"
		".on_sty  {background:#00a000;}"
		".bar_sty {background:#a00000; color:white; width:99%%; }"
		".bar_sty td {padding:2px 0 2px 1em; }"
		".cur_sty {width:99%%; }"
		".bar     {background:black; color:white;}"
		"</style>"
		"</head><body>"
		"<div>State: %s</div>"
		"<div>Time left %s: %dm%ds</div>"
		"<div>On-cycle: %dm%ds, Off-cycle: %dm%ds, Total cycle: %dm%ds</div>"
		"<div>Current time: %dm%ds</div>"
		"<table class=bar_sty><tr>"
		//          \/ ON_SECS percentage
		"<td width='%f%%' class=on_sty>ON</td><td>OFF</td></tr></table>"
		"<table class=cur_sty><tr>"
		//          \/ cur_secs percentage
		"<td width='%f%%'>&nbsp;</td>"
		"<td width='1%%' class=bar>↑</td><td>&nbsp;</td></tr></table>"
		"<div>[<a href=/sleep>Off</a> | <a href=/reset>On</a> ]</div>"

		"</body>"
		"</html>",
			str_curstate(),
			str_curstate(),
			MINSECS(remsecs), SECSSECS(remsecs),
			MINSECS(ON_SECS), SECSSECS(ON_SECS),
			MINSECS(OFF_SECS), SECSSECS(OFF_SECS),
			MINSECS(ON_SECS+OFF_SECS), SECSSECS(ON_SECS+OFF_SECS),
			MINSECS(secs), SECSSECS(secs),
			max((float)1.0, perc_on_cycle),
			max((float)1.0, perc_now)
		);
	server.send(200, "text/html", tmp);
}

