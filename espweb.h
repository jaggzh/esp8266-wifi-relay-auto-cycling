#ifndef __ESPWEB_H
#define __ESPWEB_H

#include <ESP8266WebServer.h>

#ifndef __IN_ESPWEB_CPP
extern ESP8266WebServer server;
#endif // __IN_ESPWEB_CPP

#define MINSECS(s)  ((int)((s)/60))
#define SECSSECS(s) ((int)((s)%60))

void setup_web();
void loop_web();   // call repeatedly

void http_root();
void http_reset(); // reset timer
void http_sleep(); // jump to sleep cycle


#endif // __ESPWEB_H

