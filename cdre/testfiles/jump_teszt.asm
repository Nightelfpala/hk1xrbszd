

section .text
global main


mainelott:
	cmp eax, 0
	jne mainutan
ide:
	cmp ebx, 2
	jnz mainutan
	jz oda
ideutan:
	cmp eax, ebx
	jnb main
	jna vege
	
main:
	mov eax, 1
	mov ebx, 2
	cmp eax, ebx
	ja mainutan
	jb mainelott

mainutan:
	cmp ebx, 2
	jne mainutan
	cmp eax, 0
	ja ide
	
oda:
	cmp eax, ebx
	jne ideutan
	
vege:
	cmp eax, ebx
	je main