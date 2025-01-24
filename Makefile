BASED_COMPILE := gcc -ggdb -o run 
SRC := checker.c mover.c
#TESTS := $(wildcard tests/*)
TESTS := tests/test_tree.c
THEFT := -Itheft/inc -Ltheft/build -ltheft

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


.PHONY: all build
