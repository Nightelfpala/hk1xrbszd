

section .text
global main

main:
	push dword 15
	inc esp
	add esp, 1
	dec esp
	sub esp, 1
	mov dword [esp], 257
	pop ebx