// Abimael Martell @ 2013

#include "todo.h"

static const char *options[] = {
  "document_root", "public",
  "listening_ports", "3000",
  NULL
};

int main(int argc, char *argv[]){
  struct mg_context *ctx;

  ctx = mg_start(options, &event_handler, NULL);

  getchar();

  mg_stop(ctx);

  return 0;
}
