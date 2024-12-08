#include "utils.h"
#include <stdio.h>
#include <emscripten/websocket.h>

// Variable to update
volatile int game_variable = 0;

// Callback for when a message is received
EM_BOOL on_message(int eventType, const EmscriptenWebSocketMessageEvent *e, void *userData)
{
    printf("Received message\n");
    if (e->isText)
    {
        // Assuming the server sends a stringified integer
        sscanf(e->data, "%d", &game_variable);
        printf("Received message: %s, updated variable: %d\n", e->data, game_variable);
    }
    return EM_TRUE;
}

// Callback for when the WebSocket opens
EM_BOOL on_open(int eventType, const EmscriptenWebSocketOpenEvent *e, void *userData)
{
    printf("WebSocket connection opened.\n");

    EMSCRIPTEN_RESULT result = emscripten_websocket_send_utf8_text(e->socket, "Hello from C code!");
    if (result != EMSCRIPTEN_RESULT_SUCCESS)
    {
        printf("Failed to send message: %d\n", result);
    }
    else
    {
        printf("Message sent: %s\n", "Hello from C code!");
    }

    return EM_TRUE;
}

// Callback for when the WebSocket closes
EM_BOOL on_close(int eventType, const EmscriptenWebSocketCloseEvent *e, void *userData)
{
    printf("WebSocket connection closed.\n");
    return EM_TRUE;
}

// Callback for when an error occurs
EM_BOOL on_error(int eventType, const EmscriptenWebSocketErrorEvent *e, void *userData)
{
    printf("WebSocket connection error.\n");
    return EM_TRUE;
}

int init_websocket()
{

    // Create WebSocket attributes
    EmscriptenWebSocketCreateAttributes attr;
    emscripten_websocket_init_create_attributes(&attr);
    attr.url = "ws://localhost:8080/ws"; // Replace with your WebSocket server URL

    // Create the WebSocket
    EMSCRIPTEN_WEBSOCKET_T ws = emscripten_websocket_new(&attr);
    if (ws <= 0)
    {
        printf("Failed to create WebSocket.\n");
        return 1;
    }

    // Register callbacks
    emscripten_websocket_set_onopen_callback(ws, NULL, on_open);
    emscripten_websocket_set_onmessage_callback(ws, NULL, on_message);
    emscripten_websocket_set_onclose_callback(ws, NULL, on_close);
    emscripten_websocket_set_onerror_callback(ws, NULL, on_error);
}

void print_message(const char *message)
{
    printf("%s\n", message);
}