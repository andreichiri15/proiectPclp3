build:
	gcc -Wall -std=c99 ./src/*.c -o paint -lSDL2

run:
	./paint

clean:
	rm paint