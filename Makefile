tres-en-raya: main
	gcc main -o tres-en-raya

main: src/main.c
	gcc -c src/main.c

clean:
	rm main tres-en-raya