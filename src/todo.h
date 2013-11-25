// Abimael Martell @ 2013

#include <stdio.h>
#include <string.h>
#include "vendor/mongoose/mongoose.h"
#include <sqlite3.h>
#include <json-c/json.h>

#include "model.h"
#include "actions.h"

#define TODO_CREATE_URL "/todos/create"
#define TODO_LIST_URL   "/todos"

extern sqlite3 *getSQLConn();
