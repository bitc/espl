section .text
	global main
	extern write
	extern split_file

main:
	push ebp
	mov ebp, esp

	; Verify that there is exactly 1 command line argument
	cmp DWORD [ebp+8], 2
	jne args_error

	; Put into ebx the command line argument
	mov ebx, [ebp+12]
	add ebx, 4
	mov ebx, DWORD [ebx]

	; Call split_file
	push 512 ; Default chunk size
	push ebx ; input_file
	call split_file
	add esp, 8

	; Return
	mov eax, 0
	pop ebp
	ret

args_error:
	push usage_msg_len
	push usage_msg
	push 0

	call write
	add esp, 12

	mov eax, 1
	pop ebp
	ret


section .data

usage_msg db 'usage: bsplit FILE',0xa
usage_msg_len equ $ - usage_msg
