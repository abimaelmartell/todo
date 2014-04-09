// Abimael Martell @ 2013
#ifndef TODO_H
#define TODO_H

#include <stdio.h>
#include <string.h>
#include <regex.h>

#include <mongoose.h>
#include <sqlite3.h>
#include <jansson.h>

/* URL's */
#define TODO_CREATE_URL   "/todos"
#define TODO_LIST_URL     "/todos"
#define TODO_UPDATE_REGEX "^\\/todos\\/[[:digit:]]"

extern sqlite3 *db;
extern struct mg_server *server;

/**
 * Event handler for mongoose
 */
extern int event_handler (struct mg_connection *conn, enum mg_event ev);

/**
 * Initialize web server and database
 */
extern void initialize (void);

/**
 * Close web server and database
 */
extern void term (void);

//
// Actions
//

/**
 * Get todos list json
 * GET /todos
 */
extern void todos_index (struct mg_connection *conn);

/**
 * Create a new todo
 * POST /todos
 */
extern void todos_create (struct mg_connection *conn);

/**
 * Update an existing todo
 * PUT /todo/:id
 */
extern void todos_update (struct mg_connection *conn, int todo_id);

/**
 * Delete an existing todo
 * DELETE /todo/:id
 */
extern void todos_delete (struct mg_connection *conn, int todo_id);

/**
 * Show an existing todo
 * GET /todo/:id
 */
extern void todos_show (struct mg_connection *conn, int todo_id);

//
// Model methods
//

#define TODO_STATUS_DEFAULT   0
#define TODO_STATUS_COMPLETED 1

/**
 * Get all todos in database
 * @return json_t (array)
 */
extern json_t *todo_find_all (void);

/**
 * Store a todo in database
 * @param char *text (todo content)
 * @return int (generated todo id)
 */
extern int todo_create (char *text);

/**
 * Find a todo by id
 * @param int todo_id
 * @return json_t (todo)
 */
extern json_t *todo_find_by_id (int todo_id);

/**
 * Update todo's attributes
 * @param int  todo_id
 * @param json_t *attributes
 * @return json_t * (updated todo)
 */
extern json_t *todo_update_attributes (int todo_id, json_t *attributes);

/**
 * Destroy todo
 * @param id todo_id
 * @return int (0 == ok, -1 == sql error)
 */
extern int todo_destroy(int todo_id);

#endif
