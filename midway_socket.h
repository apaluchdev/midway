// utils.h
#include <emscripten/websocket.h>
#ifndef MIDWAY_SOCKET_H
#define MIDWAY_SOCKET_H

void print_message(const char *message);

EM_BOOL on_message(int eventType, const EmscriptenWebSocketMessageEvent *e, void *userData);

EM_BOOL on_open(int eventType, const EmscriptenWebSocketOpenEvent *e, void *userData);

EM_BOOL on_close(int eventType, const EmscriptenWebSocketCloseEvent *e, void *userData);

EM_BOOL on_error(int eventType, const EmscriptenWebSocketErrorEvent *e, void *userData);

#endif // MIDWAY_SOCKET_H