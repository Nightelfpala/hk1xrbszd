
; this is a comment
	; this is a comment as well

section .data	; comment after keywords
	x: db 1, 2, 3
	y: dd 5
	yy: db 15

section .bss
	z: resb 3	; another comment

section .text
	global main
	
main:
	mov eax, 7
	add eax, 1
	sub eax, 2	; comment
	cmp eax, 6
jmpide:
	mov byte [z], 11
	mov [z + 1], al
	mov bx, [x]
	mov ebx, 7
	push ebx
	pop ecx
