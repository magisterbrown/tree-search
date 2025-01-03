all: build
	./run
build:
	gcc -ggdb -o run main.c

test:
	gcc -ggdb -o run test.c && ./run

test1:
	gcc -o run tests/test_line.c -I . && ./run

test1g:
	gcc -ggdb -o run tests/test_line.c -I . && gdb ./run

test1v:
	gcc -ggdb -o run tests/test_line.c -I . && valgrind ./run
