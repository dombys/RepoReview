all:
	nasm -felf32 funkcja.asm -o maluch.o
	gcc -m32 -c wywolanie.c -o main.o
	gcc -m32 -o cos main.o maluch.o
	rm -f *.o
