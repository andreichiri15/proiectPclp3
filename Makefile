build:
	gcc -Wall -std=c99 ./src/*.c -o paint -lSDL2 -lSDL2_image

run:
	./paint

clean:
	rm paint