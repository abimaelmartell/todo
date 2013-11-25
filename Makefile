CFLAGS  = -W -Wall -I. -pthread -g -pipe $(COPT)

all:
	$(CC) src/main.c vendor/mongoose/mongoose.c -o main $(CFLAGS)
