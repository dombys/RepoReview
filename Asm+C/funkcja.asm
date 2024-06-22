global dodaj
section .text

dodaj:
  enter 0,0

.add_loop:
  mov eax, [ebp+8]
  add eax, [ebp+12]
.done: 
  leave
  ret
