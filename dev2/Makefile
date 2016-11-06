CC=gcc
SRCS=devicelink.c\
		server.c

OBJS=$(SRCS:.c=.o)

EXEC=task
start:$(OBJS)
	$(CC) -o $(EXEC) $(OBJS) -lpthread
	
.c.o:
	$(CC) -o $@ -c $<
clean:
	rm -rf $(OBJS)