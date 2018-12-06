	.section	__TEXT,__text,regular,pure_instructions
	.macosx_version_min 10, 13
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
	xorl	%eax, %eax
	movl	$0, -4(%rbp)
	movq	$12, -16(%rbp)
	movq	$21, -24(%rbp)
	movq	-16(%rbp), %rcx
	movq	%rcx, -32(%rbp)
	movq	-24(%rbp), %rcx
	movq	%rcx, -16(%rbp)
	movq	-32(%rbp), %rcx
	movq	%rcx, -24(%rbp)
	popq	%rbp
	retq
	.cfi_endproc
                                        ## -- End function

.subsections_via_symbols
