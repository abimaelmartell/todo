// Abimael Martell @ 2013

#include "todo.h"

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
