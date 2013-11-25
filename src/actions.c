// Abimael Martell @ 2013

#include "todo.h"

void todos_index(struct mg_connection *conn, const struct mg_request_info *request_info){
  char *todos = todo_findAll();
  mg_printf(conn,
    "HTTP/1.1 200 OK\r\n"
    "Content-Type: application/json; charset=utf-8\r\n"
    "Content-Length: %d\r\n"
    "\r\n"
    "%s",
    (int) strlen(todos), todos
  );
}


void todos_create(struct mg_connection *conn, const struct mg_request_info *request_info){
}
