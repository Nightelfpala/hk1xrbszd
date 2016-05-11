
section .data
	x: db 2
section .bss
	y: resw 1

section .text

global kezdes

neittkezdj:
	push dword 126
	jmp vege
	
section .data
	z: dw 300

section .text

kezdes:
	mov eax, 2
	jmp neittkezdj

vege:
	pop ebx