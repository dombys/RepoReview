all:
	nasm -felf32 funkcja.asm -o maluch.o
	gcc -m32 -g -c wywolanie.c -o main.o
	gcc -m32 -g -o cos main.o maluch.o
