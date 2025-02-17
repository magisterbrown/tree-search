all: build 
	python3 dataloader.py

build:
	gcc -o loader.so -shared dataloader.c

test:
	gcc -ggdb -g3 -o run dataloader.c  && ./run 


