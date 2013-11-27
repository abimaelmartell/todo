// Abimael Martell @ 2013

#define TODO_STATUS_DEFAULT   0
#define TODO_STATUS_COMPLETED 1

extern json_object *todo_findAll();
extern int todo_create(char *text);
extern json_object *todo_findByID(int todo_id);
extern json_object *todo_updateAttributes(int todo_id, json_object *attributes);
