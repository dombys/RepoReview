global obrobka
section .text
; ebp+8 - tablica sampli
; ebp+12 - liczba sampli
; ebp+16 - wzmocnienie
; ebp+20 - opóźnienie próbki
;set args kopiastart.wav 0.5 0.6
obrobka:
  	enter 0,0
	movups xmm0, [ebp+16] ;wstawiamy wzmocnienie do xmm0
	mov esi, [ebp+8] ;offset tablicy
	mov ebx, [ebp+20] ;liczba opóźnionych sampla
	sub dword[ebp+12], ebx
	shl ebx, 1
	;mamy nr sampla od którego zaczynamy
	;tworzymy offset teraz dla s[t] modyfikowanych
	lea edi, [esi + ebx] ;efektywny adres komórki, którą zmienimy proszę
.loop:
	movaps xmm2, [edi] ;ten obecny
	sub edi, ebx
	movaps xmm3, [edi] ;ten opóźniony
	add edi, ebx ;przywracamy
	pmulhw xmm3,xmm0
	paddsw xmm2,xmm3
	movaps [edi], xmm2
	add edi, 16
	sub dword[ebp+12],8
	jg .loop
.done:
 	leave
  	ret
