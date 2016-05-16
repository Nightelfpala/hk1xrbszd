
section .data	; comment after keywords
	x: db 1, 2, 3
	y: dd 5
	yy: db 15

section .bss
	z: resb 3

section .text

global main


main:
	inc eax
	