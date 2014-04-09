// Abimael Martell @ 2013

extern void todos_index (struct mg_connection *conn);
extern void todos_create (struct mg_connection *conn);
extern void todos_update (struct mg_connection *conn, int todo_id);
extern void todos_delete (struct mg_connection *conn, int todo_id);
extern void todos_show (struct mg_connection *conn, int todo_id);
