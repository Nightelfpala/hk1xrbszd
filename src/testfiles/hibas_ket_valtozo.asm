

section .bss
	x: resb 2
	y: resw 3
	x: resd 1

section .text

global main

main:
	mov ecx, 16