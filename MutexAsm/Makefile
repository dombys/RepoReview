all:
	nasm -felf32 -g Mutextry1.asm -o obrobka.o
	gcc -m32 -c starter.c -o main.o
	gcc -m32 -no-pie -o mutex main.o obrobka.o
	rm -f *.o
