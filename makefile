all: calc format

calc: calc.c
	gcc -Wall -std=c99 -g -o calc calc.c
format: format.c
	gcc -Wall -g -o format format.c
clean:
	rm calc format
