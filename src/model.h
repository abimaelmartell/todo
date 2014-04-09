// Abimael Martell @ 2013

#define TODO_STATUS_DEFAULT   0
#define TODO_STATUS_COMPLETED 1

extern json_t *todo_findAll();
extern int todo_create(char *text);
extern json_t *todo_findByID(int todo_id);
extern json_t *todo_updateAttributes(int todo_id, json_t *attributes);
extern int todo_destroy(int todo_id);
