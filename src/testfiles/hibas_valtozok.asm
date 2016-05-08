
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
	mov eax, [zz + 1]
	add ebx, [zz - 1]
	mov ecx, [zz + 2] ; hiba
