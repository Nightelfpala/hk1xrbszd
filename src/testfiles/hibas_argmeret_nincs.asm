

section .text

global m

m:
	mov eax, 16
	push eax
	mov ebp, esp
	mul dword 2
	push eax
	mov [esp], [ebp]