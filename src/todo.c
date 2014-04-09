// Abimael Martell @ 2013

#include "todo.h"

sqlite3 *db;
struct mg_server *server;

int event_handler(struct mg_connection *conn, enum mg_event ev){
  regex_t regex;
  int rc;

  if(ev == MG_AUTH) return MG_TRUE;

  if(ev != MG_REQUEST) return MG_FALSE;

  printf("\x1B[0;32m[%s]\x1B[0m %s\n",
    conn->request_method,
    conn->uri
  );

  rc = regcomp(&regex, TODO_UPDATE_REGEX, 0);

  if(strcmp(conn->uri, TODO_LIST_URL) == 0 &&
          strcmp(conn->request_method, "GET") == 0){
    todos_index(conn);
  }else if(strcmp(conn->uri, TODO_CREATE_URL) == 0 &&
          strcmp(conn->request_method, "POST") == 0){
    todos_create(conn);
  }else if(regexec(&regex, conn->uri, 0, NULL, 0) == 0){
    int todo_id = atoi(&conn->uri[7]);
    if(strcmp(conn->request_method, "PUT") == 0){
      todos_update(conn, todo_id);
    }else if(strcmp(conn->request_method, "DELETE") == 0){
      todos_delete(conn, todo_id);
    }else if(strcmp(conn->request_method, "GET") == 0){
      todos_show(conn, todo_id);
    }
  }

  regfree(&regex);

  return 0;
}

void initialize(){
  int rc;

  rc = sqlite3_open("data/todos.db", &db);
  if(rc){
    printf("Cant open database %s\n", sqlite3_errmsg(db));
    sqlite3_close(db);
    return;
  }

  server = mg_create_server(NULL, event_handler);

  mg_set_option(server, "document_root", "public");
  mg_set_option(server, "listening_port", "3000");

  printf("Starting on port %s\n", mg_get_option(server, "listening_port"));
  for (;;) {
    mg_poll_server(server, 1000);
  }
}

void term(){
  sqlite3_close(db);
  mg_destroy_server(&server);
}
