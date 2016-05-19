

section .data
	x: dw 1, 2
	y: db 6, 8, 123
	z: dd 2
section .text
global main

main:
	mov eax, 1
x:
	inc dword [x]
	cmp word [x], 2
	je x
	mov ebx, 6