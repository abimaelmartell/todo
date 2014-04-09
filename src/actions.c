// Abimael Martell @ 2013

#include "todo.h"

void todos_index (struct mg_connection *conn)
{
    json_t *todos = todo_find_all();

    const char *todos_string = json_dumps(todos, 0);

    mg_printf(conn,
        "HTTP/1.1 200 OK\r\n"
        "Content-Type: application/json; charset=utf-8\r\n"
        "Content-Length: %d\r\n"
        "\r\n"
        "%s",
        (int) strlen(todos_string), todos_string
    );

    json_decref(todos);
}

void todos_create (struct mg_connection *conn)
{
    int id;
    json_t *data, *text, *todo;
    json_error_t error;

    data = json_loads(conn->content, 0, &error);

    if (data == NULL) {
        // json error
        fprintf(stderr, "error: on line %d: %s\n", error.line, error.text);
        return;
    }

    text = json_object_get(data, "text");

    const char *todo_text = json_string_value(text);

    id = todo_create((char *) todo_text);

    if (id != -1) {
        todo = todo_find_by_id(id);

        const char *todo_string = json_dumps(todo, 0);

        mg_printf(conn,
            "HTTP/1.1 200 OK\r\n"
            "Content-Type: application/json; charset=utf-8\r\n"
            "Content-Length: %d\r\n"
            "\r\n"
            "%s",
            (int) strlen(todo_string), todo_string
        );

        json_decref(todo);
    }
    json_decref(data);
}

void todos_update (struct mg_connection *conn, int todo_id)
{
    json_t *data, *todo;
    json_error_t error;

    data = json_loads(conn->content, 0, &error);

    if (data == NULL) {
        // json error
        fprintf(stderr, "error: on line %d: %s\n", error.line, error.text);
        return;
    }

    todo = todo_update_attributes(todo_id, data);

    const char *todo_string = json_dumps(todo, 0);

    mg_printf(conn,
        "HTTP/1.1 200 OK\r\n"
        "Content-Type: application/json; charset=utf-8\r\n"
        "Content-Length: %d\r\n"
        "\r\n"
        "%s",
        (int) strlen(todo_string), todo_string
    );

    json_decref(todo);
    json_decref(data);
}

void todos_delete (struct mg_connection *conn, int todo_id)
{
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

void todos_show (struct mg_connection *conn, int todo_id)
{
    json_t *todo = todo_find_by_id(todo_id);

    if (todo) {
        const char *todo_json = json_dumps(todo, 0);

        mg_printf(conn,
            "HTTP/1.1 200 OK\r\n"
            "Content-Type: application/json; charset=utf-8\r\n"
            "Content-Length: %d\r\n"
            "\r\n"
            "%s",
            (int) strlen(todo_json), todo_json
        );

        json_decref(todo);
    }
}
