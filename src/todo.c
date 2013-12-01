// Abimael Martell @ 2013

#include "todo.h"

sqlite3 *db;
struct mg_context *ctx;

static const char *options[] = {
  "document_root", "public",
  "listening_ports", "3000",
  NULL
};

int event_handler(struct mg_event *event){
  struct mg_request_info *request_info = event->request_info;
  struct mg_connection *conn = event->conn;
  regex_t regex;
  int rc;
  const char *override_method;

  if (event->type != MG_REQUEST_BEGIN) return 0;

  override_method = mg_get_header(conn, HTTP_METHOD_HEADER);

  printf("\x1B[0;32m[%s]\x1B[0m %s\n",
    override_method ? override_method : request_info->request_method,
    request_info->uri
  );

  rc = regcomp(&regex, TODO_UPDATE_REGEX, 0);

  if(strcmp(request_info->uri, TODO_LIST_URL) == 0 &&
          strcmp(request_info->request_method, "GET") == 0){
    todos_index(conn);
  }else if(strcmp(request_info->uri, TODO_CREATE_URL) == 0 &&
          strcmp(request_info->request_method, "POST") == 0){
    todos_create(conn);
  }else if(regexec(&regex, request_info->uri, 0, NULL, 0) == 0){
    int todo_id = atoi(&request_info->uri[7]);
    if(strcmp(override_method, "PUT") == 0){
      todos_update(conn, todo_id);
    }else if(strcmp(override_method, "DELETE") == 0){
      todos_delete(conn, todo_id);
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

  ctx = mg_start(options, &event_handler, NULL);
}

void term(){
  sqlite3_close(db);
  mg_stop(ctx);
}
