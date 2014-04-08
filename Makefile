JSON_HOME = vendor/json-c
JSON_INC = $(JSON_HOME)
JSON_LIB = $(JSON_HOME)/.libs/libjson-c.a

SQLITE_HOME = vendor/sqlite3
SQLITE_INC = $(SQLITE_HOME)
SQLITE_SOURCE = $(SQLITE_HOME)/sqlite3.c

MONGOOSE_HOME = vendor/mongoose
MONGOOSE_INC = $(MONGOOSE_HOME)
MONGOOSE_SOURCE = $(MONGOOSE_HOME)/mongoose.c

OBJECTS = src/actions.o src/model.o src/todo.o src/main.o
CFLAGS = -std=c99 -W -Wall -Werror -Wextra -I. -I$(JSON_INC) -I$(SQLITE_INC) -I$(MONGOOSE_INC)
LIBS = -lpthread -ldl -lc -ldl $(JSON_LIB)
TARGET = todo

.PHONY: default all clean

default: $(JSON_LIB) $(TARGET)
all: default

%.o: %.c $(CIVETWEB_LIB)
	$(CC) -c $< -o $@ $(INC) $(CFLAGS)

$(JSON_LIB):
	-cd $(JSON_HOME) && make clean
	cd $(JSON_HOME) && ./autogen.sh && ./configure && make

$(TARGET): $(JSON_LIB) $(OBJECTS)
	$(CC) $(OBJECTS) $(MONGOOSE_SOURCE) $(SQLITE_SOURCE) -o $(TARGET) $(CFLAGS) $(LIBS)

clean:
	rm src/*.o
	rm todo
