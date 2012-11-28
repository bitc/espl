section .text
	global malami
malami:
	push	ebp
	mov	ebp, esp
	sub	esp, 4
	mov	DWORD [ebp-4], 0
	jmp	.L2
.L3:
	mov	eax, DWORD [ebp-4]
	mov ebx, eax
	sal eax, 3
	sal ebx, 1
	add eax, ebx
	mov	ebx, DWORD [ebp+8]
	movzx	ebx, BYTE [ebx]
	movsx	ebx, bl
	add	eax, ebx
	sub	eax, 48
	mov	DWORD [ebp-4], eax
	add	DWORD [ebp+8], 1
.L2:
	mov	eax, DWORD [ebp+8]
	movzx	eax, BYTE [eax]
	test	al, al
	jne	.L3
	mov	eax, DWORD [ebp-4]
	mov esp, ebp
	pop ebp
	ret
