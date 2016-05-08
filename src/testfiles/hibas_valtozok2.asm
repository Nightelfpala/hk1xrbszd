
section .data
	x: db 1, 2, 3
	y: dd 5
	yy: db 15

section .bss
	z: resb 3
	
section .data
	zz: db 19, 18, 17, 16, 15

section .text
	global main
	
main:
	mov eax, [zz - 11]
	mov ecx, [zz - 12] ; hiba
