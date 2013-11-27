// Abimael Martell @ 2013

#include "todo.h"

json_object *todo_findAll(){
  sqlite3_stmt *stmt;
  json_object *todos, *todo, *id, *text, *status;
  int rc;

  sqlite3 *db = getSQLConn();
  todos = json_object_new_array();

  char sql[] = "SELECT * FROM todos";
  rc = sqlite3_prepare_v2(db, sql, sizeof(sql), &stmt, NULL);
  while(sqlite3_step(stmt) == SQLITE_ROW){
    todo = json_object_new_object();
    id = json_object_new_int(sqlite3_column_int(stmt, 0));
    text = json_object_new_string((const char *)sqlite3_column_text(stmt, 1));
    status = json_object_new_int(sqlite3_column_int(stmt, 2));

    json_object_object_add(todo, "id", id);
    json_object_object_add(todo, "text", text);
    json_object_object_add(todo, "status", status);

    json_object_array_add(todos, todo);
  }

  sqlite3_close(db);
  return todos;
}

int todo_create(char *text){
  char sql[1000], *errBuf;
  int rc, return_id;

  sqlite3 *db = getSQLConn();

  sprintf(sql, "INSERT INTO todos (text) VALUES ('%s')", text);

  rc = sqlite3_exec(db, sql, NULL, NULL, &errBuf);

  if(rc != SQLITE_OK){
    printf("SQL Error: %s\n", errBuf);
    return -1;
  }

  return_id = sqlite3_last_insert_rowid(db);

  sqlite3_close(db);
  return return_id;
}

json_object *todo_findByID(int todo_id){
  char sql[1000];
  int rc;
  sqlite3_stmt *stmt;
  json_object *todo = json_object_new_object(), *id, *text, *status;

  sqlite3 *db = getSQLConn();
  sprintf(sql, "SELECT * FROM todos WHERE id=%d", todo_id);

  rc = sqlite3_prepare_v2(db, sql, sizeof(sql), &stmt, NULL);
  if(sqlite3_step(stmt) == SQLITE_ERROR){
    printf("SQL Error: %s\n", sqlite3_errmsg(db));
    return NULL;
  }else{
    id = json_object_new_int(sqlite3_column_int(stmt, 0));
    text = json_object_new_string((const char *)sqlite3_column_text(stmt, 1));
    status = json_object_new_int(sqlite3_column_int(stmt, 2));

    json_object_object_add(todo, "id", id);
    json_object_object_add(todo, "text", text);
    json_object_object_add(todo, "status", status);
  }

  sqlite3_finalize(stmt);
  sqlite3_close(db);
  return todo;
}

json_object *todo_updateAttributes(int todo_id, json_object *todo){
  json_object *text, *status;
  sqlite3 *db;
  char sql[1000], *errBuf;
  int rc;

  text = json_object_object_get(todo, "text");
  status = json_object_object_get(todo, "status");

  db = getSQLConn();

  sprintf(sql,
    "UPDATE todos SET text='%s', status='%d' WHERE id='%d'",
    json_object_get_string(text),
    json_object_get_int(status),
    todo_id
  );

  rc = sqlite3_exec(db, sql, NULL, NULL, &errBuf);

  if(rc != SQLITE_OK){
    printf("SQL Error: %s\n", errBuf);
    sqlite3_close(db);
    return NULL;
  }

  sqlite3_close(db);
  return todo;
}

int todo_destroy(int todo_id){
  sqlite3 *db;
  int rc;
  char sql[1000], *errBuf;

  db = getSQLConn();

  sprintf(sql, "DELETE FROM todos WHERE id=%d", todo_id);

  rc = sqlite3_exec(db, sql, NULL, NULL, &errBuf);

  if(rc != SQLITE_OK){
    printf("SQL Error: %s\n", errBuf);
    sqlite3_close(db);
    return -1;
  }

  sqlite3_close(db);
  return 0;
}

