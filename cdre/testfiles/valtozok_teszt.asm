
section .data
	x: db 1, 2, 3
	y: dd 5
	yy: db 15

section .bss
	z: resb 3

section .text
	global main
	
main:
	mov eax, 256 * 256 * 3 + 256 * 9 + 42
	push dword 98
	mov byte [z], 11
	mov [z + 1], al
	mov eax, [esp]
	mov [esp], eax
	mov [y], eax
	mov bx, [x]
	pop dword [x]
	inc dword [x]
	dec word [z]
	
	add dword [y], 41
	add dword [y + 2], 123
	sub dword [y], 256 * 256 * 8 + 13
	mov eax, 2
	mul dword [x]
	mov dword [y], 3
	mov eax, 256 * 2 + 9
	div dword [y]
	push word [z]
	push word [x]
	pop dword [x]