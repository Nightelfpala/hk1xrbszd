
section .text
global main

main:
	push dword 4
	call factorial
	
	jmp kilep
	
factorial:
	push ebp
	push ebx
	mov ebp, esp
	add ebp, 12
	mov ebx, [ebp]
	
	cmp ebx, 0
	je fact0
	
	dec ebx
	push ebx
	inc ebx
	call factorial
	mul ebx
	pop ebx
	
	jmp end
fact0:
	mov eax, 1
end:
	pop ebx
	pop ebp
	ret
	
kilep:
	pop ecx