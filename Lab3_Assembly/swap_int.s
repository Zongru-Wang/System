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
	movl	$12, -8(%rbp)
	movl	$21, -12(%rbp)
	movl	-8(%rbp), %ecx
	movl	%ecx, -16(%rbp)
	movl	-12(%rbp), %ecx
	movl	%ecx, -8(%rbp)
	movl	-16(%rbp), %ecx
	movl	%ecx, -12(%rbp)
	popq	%rbp
	retq
	.cfi_endproc
                                        ## -- End function

.subsections_via_symbols
