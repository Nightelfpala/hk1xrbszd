
section .text

global main

main:
	mov edx, 256 * 7 + 53
	mov eax, 256 * 256 * 256 * 13 + 256 * 256 * 11 + 256 * 7 + 256 * 5
	mov ecx, 17
	div ecx