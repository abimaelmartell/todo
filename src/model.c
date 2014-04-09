// Abimael Martell @ 2014
// See LICENSE

#include "todo.h"

json_t *todo_find_all (void)
{
    sqlite3_mutex_enter(sqlite3_db_mutex(db));
    sqlite3_stmt *stmt;
    json_t *todos, *todo, *id, *text, *status;
    int rc;

    todos = json_array();

    char sql[] = "SELECT * FROM todos";
    rc = sqlite3_prepare_v2(db, sql, sizeof(sql), &stmt, NULL);

    while (sqlite3_step(stmt) == SQLITE_ROW) {
        todo = json_object();
        id = json_integer(sqlite3_column_int(stmt, 0));
        text = json_string((const char *)sqlite3_column_text(stmt, 1));
        status = json_integer(sqlite3_column_int(stmt, 2));

        json_object_set(todo, "id", id);
        json_object_set(todo, "text", text);
        json_object_set(todo, "status", status);

        json_array_append(todos, todo);
    }

    sqlite3_mutex_leave(sqlite3_db_mutex(db));
    return todos;
}

int todo_create (char *text)
{
    char sql[1000], *errBuf;
    int rc, return_id;

    sqlite3_mutex_enter(sqlite3_db_mutex(db));

    sprintf(sql, "INSERT INTO todos (text) VALUES ('%s')", text);

    rc = sqlite3_exec(db, sql, NULL, NULL, &errBuf);

    if (rc != SQLITE_OK) {
        printf("SQL Error: %s\n", errBuf);
        return -1;
    }

    return_id = sqlite3_last_insert_rowid(db);

    sqlite3_mutex_leave(sqlite3_db_mutex(db));
    return return_id;
}

json_t *todo_find_by_id (int todo_id)
{
    char sql[1000];
    int rc;
    sqlite3_stmt *stmt;
    json_t *todo = NULL, *id, *text, *status;

    sqlite3_mutex_enter(sqlite3_db_mutex(db));
    sprintf(sql, "SELECT * FROM todos WHERE id=%d", todo_id);

    rc = sqlite3_prepare_v2(db, sql, sizeof(sql), &stmt, NULL);

    rc = sqlite3_step(stmt);

    if (rc == SQLITE_ERROR) {
        printf("SQL Error: %s\n", sqlite3_errmsg(db));
        return NULL;
    } else if(rc == SQLITE_ROW) {
        todo = json_object();

        id = json_integer(sqlite3_column_int(stmt, 0));
        text = json_string((const char *)sqlite3_column_text(stmt, 1));
        status = json_integer(sqlite3_column_int(stmt, 2));

        json_object_set(todo, "id", id);
        json_object_set(todo, "text", text);
        json_object_set(todo, "status", status);
    }

    sqlite3_finalize(stmt);
    sqlite3_mutex_leave(sqlite3_db_mutex(db));

    return todo;
}

json_t *todo_update_attributes (int todo_id, json_t *todo)
{
    json_t *text, *status;
    char sql[1000], *errBuf;
    int rc;

    text = json_object_get(todo, "text");
    status = json_object_get(todo, "status");

    sqlite3_mutex_enter(sqlite3_db_mutex(db));

    sprintf(sql,
        "UPDATE todos SET text='%s', status='%d' WHERE id='%d'",
        json_string_value(text),
        (int) json_integer_value(status),
        todo_id
    );

    rc = sqlite3_exec(db, sql, NULL, NULL, &errBuf);

    if (rc != SQLITE_OK) {
        printf("SQL Error: %s\n", errBuf);
        sqlite3_close(db);
        return NULL;
    }

    sqlite3_mutex_leave(sqlite3_db_mutex(db));
    return todo;
}

int todo_destroy (int todo_id)
{
    int rc;
    char sql[1000], *errBuf;

    sqlite3_mutex_enter(sqlite3_db_mutex(db));

    sprintf(sql, "DELETE FROM todos WHERE id=%d", todo_id);

    rc = sqlite3_exec(db, sql, NULL, NULL, &errBuf);

    if (rc != SQLITE_OK) {
        printf("SQL Error: %s\n", errBuf);
        sqlite3_close(db);
        return -1;
    }

    sqlite3_mutex_leave(sqlite3_db_mutex(db));
    return 0;
}
