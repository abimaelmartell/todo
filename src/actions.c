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
  char post_data[1024];
  int post_len, id;
  json_object *data, *text, *todo;

  post_len = mg_read(conn, post_data, sizeof(post_data));

  data = json_tokener_parse(post_data);

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
