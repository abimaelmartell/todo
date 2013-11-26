JSON_HOME = vendor/json-c
JSON_INC = $(JSON_HOME)
JSON_LIB = $(JSON_HOME)/.libs/libjson-c.a

SQLITE_HOME = vendor/sqlite3
SQLITE_INC = $(SQLITE_HOME)
SQLITE_SOURCE = $(SQLITE_HOME)/sqlite3.c

MONGOOSE_HOME = vendor/mongoose
MONGOOSE_INC = $(MONGOOSE_HOME)
MONGOOSE_SOURCE = $(MONGOOSE_HOME)/mongoose.c

CFLAGS  = -W -Wall -I. -I$(JSON_INC)
LIBS = -lsqlite3 -ljson-c $(JSON_LIB)
TARGET = todo


.PHONY: default all clean

default: $(JSON_LIB) $(TARGET)
all: default

$(JSON_LIB):
	cd $(JSON_HOME); ./autogen.sh; ./configure; make

$(TARGET): $(JSON_LIB)
	$(CC) src/main.c src/model.c src/actions.c src/todo.c $(MONGOOSE_SOURCE) $(SQLITE_SOURCE) -o $(TARGET) $(CFLAGS) $(LIBS)

clean:
	rm todo
