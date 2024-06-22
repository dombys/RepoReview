section .data
msg db 'Niewystarczajaco funduszy. Odmowa wyplaty.', 10,0
msg1 db 'Dokonano wyplaty.', 10,0
balance dd 1000 ;deklaruje 4 bajtowy (32-bitowa) stan konta - roboczo 1000
mutexvar dd 0 ;zmienna do okreslania czy wartosc dostepna czy nie
sleep_time dd 5

global withdrawing
section .text
extern printf, sleep

withdrawing:
	enter 0,0
	.check_mutex_status:
	cmp dword [mutexvar],0
	je .acquire_mutex
	PAUSE ;procesor dostaje informacje, ze to petla spinlock
	jmp .check_mutex_status
    	.acquire_mutex:
        mov eax, 0
       	mov ecx, 1
        lock cmpxchg [mutexvar], ecx ;
        jnz .check_mutex_status
	; Sekcja krytyczna
	push dword [sleep_time] ;dodane tylko, by w gdb mozna bylo
	call sleep				;jak 2. watek sie zapetla na spinlocku
	add esp, 4
    	mov ecx, dword [balance]  ; Załaduj saldo konta do ECX
    	cmp ecx, 700                ; Sprawdź, czy saldo jest wystarczające
    	jb .insufficient             
	sub ecx, 700                
    	mov dword [balance], ecx  ; Zaktualizuj saldo konta
	push msg1
	call printf
	add esp, 4
    	; Zwolnienie mutexu
    	mov dword [mutexvar], 0
    	jmp .done

	.insufficient:
    	; Obsługa niewystarczających środków
   	 push msg
	 call printf
	 add esp,4

    	; Zwolnienie mutexu
    	mov dword [mutexvar], 0

    	jmp .done

	.done:
	mov eax, [balance]
    	leave
    	ret


