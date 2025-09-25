#ifndef WEBSERVERHANDLER_H
#define WEBSERVERHANDLER_H

#include <Arduino.h>
#include <WebServer.h>

// publikus függvények
void webserver_init(uint16_t port);
void webserver_handle();

#endif
