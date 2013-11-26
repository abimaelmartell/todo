// Abimael Martell @ 2013

#include <stdio.h>
#include <string.h>
#include <mongoose.h>
#include <sqlite3.h>
#include <json.h>
#include <regex.h>

#include "model.h"
#include "actions.h"

#define TODO_CREATE_URL "/todos"
#define TODO_LIST_URL   "/todos"

extern int event_handler(struct mg_event *event);
extern sqlite3 *getSQLConn();
