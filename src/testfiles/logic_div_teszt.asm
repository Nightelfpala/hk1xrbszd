
section .text
global main



main:
logical:
	mov eax, 256 + 128
	mov ebx, 256
	mov ecx, eax
	or ecx, ebx
	and ecx, ebx
	add ecx, 256
	xor ecx, ebx
division:
	mov eax, 50
	;mov ecx, 7
	div dword 7