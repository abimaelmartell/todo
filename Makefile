JANSSON_HOME = vendor/jansson
JANSSON_INC = $(JANSSON_HOME)/src
JANSSON_LIB = $(JANSSON_HOME)/src/.libs/libjansson.a

SQLITE_HOME = vendor/sqlite3
SQLITE_INC = $(SQLITE_HOME)
SQLITE_SOURCE = $(SQLITE_HOME)/sqlite3.c

MONGOOSE_HOME = vendor/mongoose
MONGOOSE_INC = $(MONGOOSE_HOME)
MONGOOSE_SOURCE = $(MONGOOSE_HOME)/mongoose.c

OBJECTS = src/actions.o src/model.o src/todo.o src/main.o
CFLAGS = -std=c99 -W -Wall -Werror -Wextra
INC = -I. -I$(JANSSON_INC) -I$(SQLITE_INC) -I$(MONGOOSE_INC)
LIBS = -lpthread -ldl -lc -ldl $(JANSSON_LIB)
TARGET = todo

.PHONY: default all clean

default: $(JANSSON_LIB) $(TARGET)
all: default

%.o: %.c $(CIVETWEB_LIB)
	$(CC) -c $< -o $@ $(INC) $(CFLAGS)

$(JANSSON_LIB):
	cd $(JANSSON_HOME) && autoreconf -i  && ./configure && make

$(TARGET): $(JANSSON_LIB) $(OBJECTS)
	$(CC) $(OBJECTS) $(MONGOOSE_SOURCE) $(SQLITE_SOURCE) -o $(TARGET) $(CFLAGS) $(LIBS)

clean:
	rm src/*.o
	rm todo
