// Abimael Martell @ 2013

#include <stdio.h>
#include <string.h>
#include <mongoose.h>
#include <sqlite3.h>
#include <jansson.h>
#include <regex.h>

#include "model.h"
#include "actions.h"

#define TODO_CREATE_URL   "/todos"
#define TODO_LIST_URL     "/todos"
#define TODO_UPDATE_REGEX "^\\/todos\\/[[:digit:]]"

extern sqlite3 *db;
extern struct mg_server *server;
extern int event_handler (struct mg_connection *conn, enum mg_event ev);
extern void initialize (void);
extern void term (void);
