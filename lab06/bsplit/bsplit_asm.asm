section .text
	global main
	global process_chunk
	extern split_file
	extern eof

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
	mov eax, 4 ; write system call
	mov ebx, 2 ; stderr
	mov ecx, usage_msg
	mov edx, usage_msg_len
	int 0x80

	mov eax, 1
	pop ebp
	ret


process_chunk:
	push ebp
	mov ebp, esp

	; Open the chunk file
	mov eax, 5 ; open system call
	mov ebx, DWORD [ebp+16]
	mov ecx, 577 ; 1 | 64 | 512
	mov edx, 666o
	int 0x80

	; Store the file descriptor
	mov DWORD [ebp-4], eax

	; TODO Check error condition: eax < 0

	; Set a memory location to 0 as an initial dummy value for the checksum
	mov DWORD [ebp-8], 0

	mov DWORD [ebp-12], 0 ; checksum
	mov DWORD [ebp-16], 0 ; num_bytes

	mov ebx, eax ; previous file descriptor
	mov eax, 4 ; write system call
	mov ecx, ebp
	sub ecx, 4
	mov edx, 4
	int 0x80

read_loop:
	mov DWORD [ebp-8], 0
	mov eax, 3 ; read system call
	mov ebx, [ebp+8]
	mov ecx, ebp
	sub ecx, 8
	mov edx, 4
	int 0x80

	; Advance num_bytes
	add DWORD [ebp-16], eax

	; Update checksum
	mov ebx, DWORD [ebp-8]
	xor DWORD [ebp-12], ebx

	; Store the number of bytes read in edx
	mov edx, eax
	mov eax, 4 ; write system call
	mov ebx, [ebp-8]
	; Same ecx as before
	int 0x80

	cmp edx, 4
	jl end_of_input

	cmp DWORD [ebp-16], 512
	je finish

	jmp read_loop
end_of_input:
	mov DWORD [eof], 1
	; TODO set eof=1

finish:
	mov eax, 19 ; lseek system call
	mov ebx, [ebp-4]
	mov ecx, 0
	mov edx, 0
	int 0x80

	mov eax, 4 ; write system call
	; Same ebx as above
	mov ecx, [ebp-12] ; checksum value
	mov edx, 4
	int 0x80

	mov eax, 6 ; close system call
	; Same ebx as above
	int 0x80

	mov eax, 1
	pop ebp
	ret

section .data

usage_msg db 'usage: bsplit FILE',0xa
usage_msg_len equ $ - usage_msg
