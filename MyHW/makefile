all: main.o func.o
	gcc -m32 -std=c99 main.o func.o -o master -lm
main.o: main.c
	gcc -m32 -std=c99 -c main.c -o main.o
func.o: func.asm
	nasm -f elf32 func.asm -o func.o
clean:
	rm -rf *.o
	