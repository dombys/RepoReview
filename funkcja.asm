global dodaj
section .text

dodaj:
enter 0,0

mov esi, [ebp+8] ;tablica 1, adres 1. elementu tablicy
mov edi, [ebp+12] ;tablica 2, adres 1. elementu tablicy
mov ecx, [ebp+16] ;ile liczb (ile razy ma przejść pętla dodawania)

.sumator:
add esi, ecx ;przejdź do ostatniego elementu tablicy 1
add edi, ecx ;przejdź do ostatniego elementu tablicy 2
mov al, byte [esi] ;pobierz wartość elementu ostatniego tablicy 1
mov bl, byte [edi]
add al, bl
cmp al, 0x10 ;czy więcej niż 0x0F+1 ?
jge .do_reszty
mov [esi], al
jmp .add_loop

.do_reszty:
sub al, 0x10
mov [esi], al ;wstaw pomniejszoną wartość w tablicy 1
jmp .is_carry

.is_carry:
cmp esi, 0 ;sprawdz czy bajt, na którym jesteśmy nie jest ostatni (0 wiodące)
je .last_add
dec esi
mov al, [esi]
cmp al, 0x0F
je .change_zero
add al, 0x01
mov [esi], al
jmp .add_loop

.change_zero:
mov al, 0
mov [esi], al
jmp .is_carry

.last_add:
mov al, 1
mov [esi], al
jmp .add_loop

.add_loop:
dec ecx
cmp ecx, 0
je .done
dec edi
mov esi, [ebp + 8] ;przywracamy wskazanie elementu w tablicy 1
add esi, ecx
mov al, byte [esi]
mov bl, byte [edi]
add al, bl
cmp al, 0x10
jge .do_reszty
mov [esi], al
jmp .add_loop

.done:
leave
ret
