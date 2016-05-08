

section .text
global main

main:
	mov ebx, 2
	
	push ebx
	mov ebp, esp
	push ebp
	pop ebp