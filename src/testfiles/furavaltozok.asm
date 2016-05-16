
section .bss
	.x: resb 1
	...y: resb 1
	__y: resb 1
	_..._: resb 1
	_Wall: resb 1
	.RvbvZU: resb 1
	_: resb 1
	...1_2_3...: resb 1

section .text

global __main

__main:
	mov al, 1
	mov [.RvbvZU], al
	mov [_..._], al
	mov [...1_2_3...], al
	
	