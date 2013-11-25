CFLAGS  = -W -Wall -I.
LIBS = -lsqlite3 -ljson-c

all:
	$(CC) src/main.c src/model.c src/actions.c src/todo.c vendor/mongoose/mongoose.c -o todo $(CFLAGS) $(LIBS)

clean:
	rm todo
