

section .text

global start

start:
	
	mov ebx, ( ( ( 255 * 256 + 255 ) * 256 ) + 255 ) * 256 + 255
	mov eax, 100
loopcimke:
	cmp eax, 0
	jna vege
	dec eax
	push ebx
	jmp loopcimke
	
vege:
	mov edx, 1
	