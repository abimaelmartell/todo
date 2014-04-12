JANSSON_HOME = vendor/jansson
JANSSON_INC = $(JANSSON_HOME)/src
JANSSON_LIB = $(JANSSON_HOME)/src/.libs/libjansson.a

SQLITE_HOME = vendor/sqlite3
SQLITE_INC = $(SQLITE_HOME)
SQLITE_OBJ = $(SQLITE_HOME)/sqlite3.o

MONGOOSE_HOME = vendor/mongoose
MONGOOSE_INC = $(MONGOOSE_HOME)
MONGOOSE_OBJ = $(MONGOOSE_HOME)/mongoose.o

OBJECTS = src/actions.o src/model.o src/todo.o src/main.o $(MONGOOSE_OBJ) $(SQLITE_OBJ)
CFLAGS = -std=c99 -W -Wall -Werror -Wextra
INC = -I. -I$(JANSSON_INC) -I$(SQLITE_INC) -I$(MONGOOSE_INC)
LIBS = -lpthread -ldl -lc -ldl $(JANSSON_LIB)
TARGET = todo

.PHONY: default all clean

default: $(JANSSON_LIB) $(TARGET)
all: default

%.o: %.c
	$(CC) -c $< -o $@ $(INC) $(CFLAGS)

$(JANSSON_LIB):
	cd $(JANSSON_HOME) && autoreconf -i  && ./configure && make

$(TARGET): $(JANSSON_LIB) $(OBJECTS)
	$(CC) $(OBJECTS) -o $(TARGET) $(CFLAGS) $(LIBS)

clean-vendors:
	rm $(SQLITE_OBJ)
	rc $(MONGOOSE_OBJ)
	cd vendor/jansson && make clean

clean:
	rm src/*.o
	rm todo
