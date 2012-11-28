section .text
	global cmpstr
cmpstr:
	push ebp
	mov ebp, esp

loop:
	mov eax, DWORD [ebp+8]
	movzx eax, BYTE [eax]
	mov ebx, DWORD [ebp+12]
	movzx ebx, BYTE [ebx]
	test eax, eax
	je test
	cmp eax, ebx
	jne test
	inc DWORD [ebp+8]
	inc DWORD [ebp+12]
	jmp loop

test:
	cmp eax, ebx
	jl less
	jg greater

equals:
	mov eax, 0
	pop ebp
	ret

greater:
	mov eax, 1
	pop ebp
	ret

less:
	mov eax, 2
	pop ebp
	ret
