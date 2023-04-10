all: tres-en-raya client server

tres-en-raya: src/main.c
	gcc src/main.c -o tres-en-raya

client: src/client.c
	gcc src/client.c -o client

server: src/server.c
	gcc src/server.c -o server

clean:
	rm tres-en-raya client server