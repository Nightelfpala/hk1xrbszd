

section .text

global nemmain


nemmain:
	push dword 5
	mov dword [esp], 1
	mov dword [esp - 4], 2