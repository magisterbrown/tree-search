BASED_COMPILE := gcc -ggdb -o run 
SHARED_COMPILE := gcc -shared -ggdb -o 
SRC := checker.c mover.c search.c
#TESTS := $(wildcard tests/*)
TESTS := tests/test_tree.c

INJECT_MAIN = $(BASED_COMPILE) $(SRC) $(1) -I . 


all: build 
	./run


debug: build
	gdb ./run

gf2: build
	gf2 ./run

grind: build
	valgrind ./run
build:
	$(BASED_COMPILE) $(SRC) $(TESTS) -I . $(THEFT)

search: base
	$(SHARED_COMPILE) libsearch.so search.c -L. -lbase -Wl,-rpath,.

base:
	$(SHARED_COMPILE) libbase.so checker.c mover.c

play: base 
	$(BASED_COMPILE) play.c  -L. -lbase -Wl,-rpath,.
	./run

attach:
	echo 0 | sudo tee /proc/sys/kernel/yama/ptrace_scope
	gf2 -p $(shell pidof ./run)

pytest:
	python -m unittest discover pytests

.PHONY: all build attach
