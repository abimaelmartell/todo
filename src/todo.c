// Abimael Martell @ 2014
// See LICENSE

#include "todo.h"

sqlite3 *db;
struct mg_server *server;

int event_handler (struct mg_connection *conn, enum mg_event ev)
{
    int rc;
    char tmpBuf[256];
    enum mg_result res = MG_FALSE;
    regex_t regex;

    if (ev == MG_AUTH) {
        return MG_TRUE;
    } else if (ev != MG_REQUEST) {
        return MG_FALSE;
    }

    sprintf(tmpBuf, "%s %s", conn->request_method, conn->uri);
    log_line(tmpBuf, LOG_INFO);

    rc = regcomp(&regex, TODO_UPDATE_REGEX, 0);

    if (strcmp(conn->uri, TODOS_URL) == 0) {
        if(strcmp(conn->request_method, "GET") == 0) {
            todos_index(conn);
            res = MG_TRUE;
        } else if (strcmp(conn->request_method, "POST") == 0) {
            todos_create(conn);
            res = MG_TRUE;
        }
    } else if (regexec(&regex, conn->uri, 0, NULL, 0) == 0) {
        int todo_id = atoi(&conn->uri[7]);
        if (strcmp(conn->request_method, "PUT") == 0) {
            todos_update(conn, todo_id);
            res = MG_TRUE;
        } else if(strcmp(conn->request_method, "DELETE") == 0) {
            todos_delete(conn, todo_id);
            res = MG_TRUE;
        } else if(strcmp(conn->request_method, "GET") == 0) {
            todos_show(conn, todo_id);
            res = MG_TRUE;
        }
    }

    regfree(&regex);

    return res;
}

void initialize (char *http_port)
{
    int rc;
    char tmpBuf[80];

    rc = sqlite3_open("data/todos.db", &db);

    if (rc) {
        sprintf(tmpBuf, "SQL error: %s", sqlite3_errmsg(db));
        log_line(tmpBuf, LOG_ERROR);
        sqlite3_close(db);
        return;
    }

    server = mg_create_server(NULL, event_handler);

    mg_set_option(server, "document_root", "public");
    mg_set_option(server, "listening_port", http_port);

    sprintf(tmpBuf, "Starting on port %s", mg_get_option(server, "listening_port"));
    log_line(tmpBuf, LOG_INFO);
  
    for (;;) {
        mg_poll_server(server, 1000);
    }
}

void term (void)
{
    sqlite3_close(db);
    mg_destroy_server(&server);
}

void log_line (char *content, enum log_level level)
{
    time_t current_time;
    struct tm *p;
    char time_str[80];

    current_time = time(NULL);
    p = localtime(&current_time);
    strftime(time_str, sizeof(time_str), "%D %r", p);

    if (level == LOG_INFO)
        printf(LOG_INFO_TPL, time_str, content);
    else if(level == LOG_ERROR)
        printf(LOG_ERROR_TPL, time_str, content);
}
