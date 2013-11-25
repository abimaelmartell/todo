// Abimael Martell @ 2013

#include "todo.h"

static const char *options[] = {
  "document_root", "public",
  "listening_ports", "3000",
  NULL
};

static int event_handler(struct mg_event *event){
  struct mg_request_info *request_info = event->request_info;
  struct mg_connection *conn = event->conn;

  if (event->type != MG_REQUEST_BEGIN) return 0;

  if(strcmp(request_info->uri, TODO_LIST_URL) == 0){
    todos_index(conn, request_info);
  }

  return 0;
}

int main(int argc, char *argv[]){
  struct mg_context *ctx;

  ctx = mg_start(options, &event_handler, NULL);

  getchar();

  mg_stop(ctx);

  return 0;
}
