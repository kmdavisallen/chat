CFLAGS= -Wall

chatclient: chatclient.c
	gcc -o chatclient chatclient.c $(CFLAGS)
clean:
	rm -f chatclient
