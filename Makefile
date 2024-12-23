all: build
	./run
build:
	gcc -ggdb -o run main.c

test:
	gcc -ggdb -o run test.c && ./run

