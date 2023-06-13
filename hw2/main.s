	.file	"main.c"
	.text
	.section	.rodata
.LC0:
	.string	"case 1"
.LC1:
	.string	"case 2"
.LC2:
	.string	"case 3"
.LC3:
	.string	"case 7"
.LC4:
	.string	"case 100"
.LC5:
	.string	"case 1131"
.LC6:
	.string	"default case"
.LC7:
	.string	"num = %d\n"
	.text
	.globl	main
	.type	main, @function
main:
.LFB0:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movl	$7, -4(%rbp)
	movl	-4(%rbp), %eax
	cmpl	$1131, %eax
	je	.L2
	cmpl	$1131, %eax
	jg	.L3
	cmpl	$100, %eax
	je	.L4
	cmpl	$100, %eax
	jg	.L3
	cmpl	$7, %eax
	je	.L5
	cmpl	$7, %eax
	jg	.L3
	cmpl	$3, %eax
	je	.L6
	cmpl	$3, %eax
	jg	.L3
	cmpl	$1, %eax
	je	.L7
	cmpl	$2, %eax
	je	.L8
	jmp	.L3
.L7:
	leaq	.LC0(%rip), %rax
	movq	%rax, %rdi
	call	puts@PLT
	jmp	.L9
.L8:
	leaq	.LC1(%rip), %rax
	movq	%rax, %rdi
	call	puts@PLT
	jmp	.L9
.L6:
	leaq	.LC2(%rip), %rax
	movq	%rax, %rdi
	call	puts@PLT
	jmp	.L9
.L5:
	leaq	.LC3(%rip), %rax
	movq	%rax, %rdi
	call	puts@PLT
	jmp	.L9
.L4:
	leaq	.LC4(%rip), %rax
	movq	%rax, %rdi
	call	puts@PLT
	jmp	.L9
.L2:
	leaq	.LC5(%rip), %rax
	movq	%rax, %rdi
	call	puts@PLT
	jmp	.L9
.L3:
	leaq	.LC6(%rip), %rax
	movq	%rax, %rdi
	call	puts@PLT
	nop
.L9:
	movl	-4(%rbp), %eax
	movl	%eax, %esi
	leaq	.LC7(%rip), %rax
	movq	%rax, %rdi
	movl	$0, %eax
	call	printf@PLT
	movl	$0, %eax
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE0:
	.size	main, .-main
	.ident	"GCC: (Ubuntu 12.1.0-2ubuntu1~22.04) 12.1.0"
	.section	.note.GNU-stack,"",@progbits
	.section	.note.gnu.property,"a"
	.align 8
	.long	1f - 0f
	.long	4f - 1f
	.long	5
0:
	.string	"GNU"
1:
	.align 8
	.long	0xc0000002
	.long	3f - 2f
2:
	.long	0x3
3:
	.align 8
4:
