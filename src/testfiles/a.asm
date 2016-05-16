

section .data
	x: db 99, 0, 0
	y: dw 28, 115
	yy: db 15
	_._: dd 100000, 10000, 1000
	z: db 10, 42, 0

section .text

global main


main:
	mov eax, 2
	mov ebx, 513