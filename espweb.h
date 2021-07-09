#ifndef __ESPWEB_H
#define __ESPWEB_H

#include <ESP8266WebServer.h>

#ifndef __IN_ESPWEB_CPP
extern ESP8266WebServer server;
#endif // __IN_ESPWEB_CPP

void setup_web();

void http_root();
void http_reset(); // reset timer
void http_sleep(); // jump to sleep cycle


#endif // __ESPWEB_H

