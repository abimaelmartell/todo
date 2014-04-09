// Abimael Martell @ 2013

#include "todo.h"

int main (int argc, char *argv[])
{
    char *http_port;

    if (argc > 1) {
        http_port = argv[1];
    } else {
        http_port = DEFAULT_HTTP_PORT;
    }

    initialize(http_port);

    term();

    return 0;
}

