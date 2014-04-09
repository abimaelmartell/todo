// Abimael Martell @ 2013

#include "todo.h"

void todos_index(struct mg_connection *conn){
  json_object *todos = todo_findAll();

  const char *todos_string = json_object_to_json_string(todos);

  mg_printf(conn,
    "HTTP/1.1 200 OK\r\n"
    "Content-Type: application/json; charset=utf-8\r\n"
    "Content-Length: %d\r\n"
    "\r\n"
    "%s",
    (int) strlen(todos_string), todos_string
  );
}


void todos_create(struct mg_connection *conn){
  int id;
  json_object *data, *text, *todo;

  data = json_tokener_parse(conn->content);

  text = json_object_object_get(data, "text");

  const char *todo_text = json_object_get_string(text);

  id = todo_create((char *) todo_text);

  if(id != -1){
    todo = todo_findByID(id);

    const char *todo_string = json_object_to_json_string(todo);

    mg_printf(conn,
      "HTTP/1.1 200 OK\r\n"
      "Content-Type: application/json; charset=utf-8\r\n"
      "Content-Length: %d\r\n"
      "\r\n"
      "%s",
      (int) strlen(todo_string), todo_string
    );
  }
}

void todos_update(struct mg_connection *conn, int todo_id){
  json_object *data, *todo;

  data = json_tokener_parse(conn->content);

  todo = todo_updateAttributes(todo_id, data);

  const char *todo_string = json_object_to_json_string(todo);

  mg_printf(conn,
    "HTTP/1.1 200 OK\r\n"
    "Content-Type: application/json; charset=utf-8\r\n"
    "Content-Length: %d\r\n"
    "\r\n"
    "%s",
    (int) strlen(todo_string), todo_string
  );
}

void todos_delete(struct mg_connection *conn, int todo_id){
  int rc = todo_destroy(todo_id);

  if (rc == 0) {
    mg_printf(conn,
      "HTTP/1.1 200 OK\r\n"
      "Content-Type: application/json; charset=utf-8\r\n"
      "Content-Length: 0\r\n"
      "\r\n"
    );
  }
}

void todos_show(struct mg_connection *conn, int todo_id){
  json_object *todo = todo_findByID(todo_id);

  if(todo){
    const char *todo_json = json_object_to_json_string(todo);

    mg_printf(conn,
      "HTTP/1.1 200 OK\r\n"
      "Content-Type: application/json; charset=utf-8\r\n"
      "Content-Length: %d\r\n"
      "\r\n"
      "%s",
      (int) strlen(todo_json), todo_json
    );
  }
}
