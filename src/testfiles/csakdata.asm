

section .data
	x: dw 2, 1
	z: db 3, 11, 16

section .text
	global main
	
main:
	mov eax, 7
	add eax, 1
	sub eax, 2
	cmp eax, 6
jmpide:
	mov byte [z], 11
	mov [z + 1], al
	mov bx, [x]
	mov ebx, 7
	push ebx
	pop ecx
