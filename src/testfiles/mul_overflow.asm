
section .text

global main

main:	; overflow multiplication test
	mov eax, 256 * 256 * 256 * 128
	mov ebx, eax
	mul ebx