gateUpnp:main.c
CC = gcc
CFLAGS = -Wall -L /usr/local/lib/ -lupnp -lixml -lpthread

gateUpnp:
	$(CC) main.c sample_util.c $(CFLAGS) -o gateUpnp

clean:
	rm -rf gateUpnp	
