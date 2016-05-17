

section .bss

	XYZ: resd 2
	
section .text
global main
main:
	mov eax, 91
	mov ebx, [ZYX]
