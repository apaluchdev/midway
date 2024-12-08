#include <stdio.h>

#ifdef PLATFORM_WEB
#include "midway_socket.h"
#endif

int main()
{
    // Check if the browser supports WebSockets

    #ifdef PLATFORM_WEB
    if (!emscripten_websocket_is_supported())
    {
        printf("WebSockets are not supported in this browser.\n");
        return 1;
    }
    print_message("Hello from midway_socket!");
    #endif

    return 0;
}
