// Abimael Martell @ 2013

#include "todo.h"

int event_handler(struct mg_event *event){
  struct mg_request_info *request_info = event->request_info;
  struct mg_connection *conn = event->conn;

  if (event->type != MG_REQUEST_BEGIN) return 0;

  if(strcmp(request_info->uri, TODO_LIST_URL) == 0){
    todos_index(conn, request_info);
  }else if(strcmp(request_info->uri, TODO_CREATE_URL) == 0 &&
          strcmp(request_info->request_method, "POST") == 0){
    todos_create(conn, request_info);
  }

  return 0;
}

sqlite3 *getSQLConn(){
  sqlite3 *db;
  int rc;

  rc = sqlite3_open("data/todos.db", &db);
  if(rc){
    printf("Cant open database %s\n", sqlite3_errmsg(db));
    sqlite3_close(db);
    return NULL;
  }

  return db;
}
