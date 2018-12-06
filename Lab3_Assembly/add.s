	.section	__TEXT,__text,regular,pure_instructions
	.macosx_version_min 10, 13
	.globl	_add                    ## -- Begin function add
	.p2align	4, 0x90
_add:                                   ## @add
	.cfi_startproc
## %bb.0:
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset %rbp, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register %rbp
	movq	%rdi, -8(%rbp)
	movq	%rsi, -16(%rbp)
	movq	-8(%rbp), %rsi
	addq	-16(%rbp), %rsi
	movq	%rsi, %rax
	popq	%rbp
	retq
	.cfi_endproc
                                        ## -- End function
	.globl	_main                   ## -- Begin function main
	.p2align	4, 0x90
_main:                                  ## @main
	.cfi_startproc
## %bb.0:
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset %rbp, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register %rbp
	subq	$32, %rsp
	movabsq	$6666666666666, %rax    ## imm = 0x610344C6AAA
	movabsq	$9999999999999, %rcx    ## imm = 0x9184E729FFF
	movq	%rcx, -8(%rbp)
	movq	%rax, -16(%rbp)
	movq	-8(%rbp), %rdi
	movq	-16(%rbp), %rsi
	callq	_add
	leaq	L_.str(%rip), %rdi
	movq	%rax, %rsi
	movb	$0, %al
	callq	_printf
	xorl	%edx, %edx
	movl	%eax, -20(%rbp)         ## 4-byte Spill
	movl	%edx, %eax
	addq	$32, %rsp
	popq	%rbp
	retq
	.cfi_endproc
                                        ## -- End function
	.section	__TEXT,__cstring,cstring_literals
L_.str:                                 ## @.str
	.asciz	"%ld"


.subsections_via_symbols
