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
	pushq	%r15
	pushq	%r14
	pushq	%r13
	pushq	%r12
	pushq	%rbx
	andq	$-32, %rsp
	subq	$672, %rsp              ## imm = 0x2A0
	.cfi_offset %rbx, -56
	.cfi_offset %r12, -48
	.cfi_offset %r13, -40
	.cfi_offset %r14, -32
	.cfi_offset %r15, -24
	leaq	L_.str.1(%rip), %rdi
	leaq	352(%rsp), %rax
	movq	___stack_chk_guard@GOTPCREL(%rip), %rcx
	movq	(%rcx), %rcx
	movq	%rcx, 640(%rsp)
	movl	$0, 476(%rsp)
	vmovups	l_main.evens(%rip), %ymm0
	vmovaps	%ymm0, 608(%rsp)
	movl	$1073741824, 540(%rsp)  ## imm = 0x40000000
	movl	$1082130432, 536(%rsp)  ## imm = 0x40800000
	movl	$1086324736, 532(%rsp)  ## imm = 0x40C00000
	movl	$1090519040, 528(%rsp)  ## imm = 0x41000000
	movl	$1092616192, 524(%rsp)  ## imm = 0x41200000
	movl	$1094713344, 520(%rsp)  ## imm = 0x41400000
	movl	$1096810496, 516(%rsp)  ## imm = 0x41600000
	movl	$1098907648, 512(%rsp)  ## imm = 0x41800000
	vmovss	532(%rsp), %xmm1        ## xmm1 = mem[0],zero,zero,zero
	vmovss	528(%rsp), %xmm2        ## xmm2 = mem[0],zero,zero,zero
	vinsertps	$16, %xmm1, %xmm2, %xmm1 ## xmm1 = xmm2[0],xmm1[0],xmm2[2,3]
	vmovss	536(%rsp), %xmm2        ## xmm2 = mem[0],zero,zero,zero
	vinsertps	$32, %xmm2, %xmm1, %xmm1 ## xmm1 = xmm1[0,1],xmm2[0],xmm1[3]
	vmovss	540(%rsp), %xmm2        ## xmm2 = mem[0],zero,zero,zero
	vinsertps	$48, %xmm2, %xmm1, %xmm1 ## xmm1 = xmm1[0,1,2],xmm2[0]
	vmovss	516(%rsp), %xmm2        ## xmm2 = mem[0],zero,zero,zero
	vmovss	512(%rsp), %xmm3        ## xmm3 = mem[0],zero,zero,zero
	vinsertps	$16, %xmm2, %xmm3, %xmm2 ## xmm2 = xmm3[0],xmm2[0],xmm3[2,3]
	vmovss	520(%rsp), %xmm3        ## xmm3 = mem[0],zero,zero,zero
	vinsertps	$32, %xmm3, %xmm2, %xmm2 ## xmm2 = xmm2[0,1],xmm3[0],xmm2[3]
	vmovss	524(%rsp), %xmm3        ## xmm3 = mem[0],zero,zero,zero
	vinsertps	$48, %xmm3, %xmm2, %xmm2 ## xmm2 = xmm2[0,1,2],xmm3[0]
                                        ## implicit-def: %ymm0
	vmovaps	%xmm2, %xmm0
	vinsertf128	$1, %xmm1, %ymm0, %ymm0
	vmovaps	%ymm0, 480(%rsp)
	vmovaps	480(%rsp), %ymm0
	vmovaps	%ymm0, 416(%rsp)
	leaq	608(%rsp), %rcx
	movq	%rcx, 408(%rsp)
	movq	408(%rsp), %rcx
	vmovss	(%rcx), %xmm1           ## xmm1 = mem[0],zero,zero,zero
	vmovss	4(%rcx), %xmm2          ## xmm2 = mem[0],zero,zero,zero
                                        ## implicit-def: %xmm3
	vcvtss2sd	%xmm1, %xmm3, %xmm0
                                        ## implicit-def: %xmm1
	vcvtss2sd	%xmm2, %xmm1, %xmm1
	vmovss	8(%rcx), %xmm2          ## xmm2 = mem[0],zero,zero,zero
                                        ## implicit-def: %xmm3
	vcvtss2sd	%xmm2, %xmm3, %xmm2
	vmovss	12(%rcx), %xmm3         ## xmm3 = mem[0],zero,zero,zero
                                        ## implicit-def: %xmm4
	vcvtss2sd	%xmm3, %xmm4, %xmm3
	vmovss	16(%rcx), %xmm4         ## xmm4 = mem[0],zero,zero,zero
                                        ## implicit-def: %xmm5
	vcvtss2sd	%xmm4, %xmm5, %xmm4
	vmovss	20(%rcx), %xmm5         ## xmm5 = mem[0],zero,zero,zero
                                        ## implicit-def: %xmm6
	vcvtss2sd	%xmm5, %xmm6, %xmm5
	vmovss	24(%rcx), %xmm6         ## xmm6 = mem[0],zero,zero,zero
                                        ## implicit-def: %xmm7
	vcvtss2sd	%xmm6, %xmm7, %xmm6
	vmovss	28(%rcx), %xmm7         ## xmm7 = mem[0],zero,zero,zero
                                        ## implicit-def: %xmm8
	vcvtss2sd	%xmm7, %xmm8, %xmm7
	leaq	L_.str(%rip), %rcx
	movb	$8, %dl
	movq	%rdi, 336(%rsp)         ## 8-byte Spill
	movq	%rcx, %rdi
	movq	%rax, 328(%rsp)         ## 8-byte Spill
	movb	%dl, %al
	vzeroupper
	callq	_printf
	movb	$97, 607(%rsp)
	movb	$98, 606(%rsp)
	movb	$99, 605(%rsp)
	movb	$100, 604(%rsp)
	movb	$101, 603(%rsp)
	movb	$102, 602(%rsp)
	movb	$103, 601(%rsp)
	movb	$104, 600(%rsp)
	movb	$105, 599(%rsp)
	movb	$106, 598(%rsp)
	movb	$107, 597(%rsp)
	movb	$108, 596(%rsp)
	movb	$109, 595(%rsp)
	movb	$110, 594(%rsp)
	movb	$111, 593(%rsp)
	movb	$112, 592(%rsp)
	movb	$113, 591(%rsp)
	movb	$114, 590(%rsp)
	movb	$115, 589(%rsp)
	movb	$116, 588(%rsp)
	movb	$117, 587(%rsp)
	movb	$118, 586(%rsp)
	movb	$119, 585(%rsp)
	movb	$120, 584(%rsp)
	movb	$121, 583(%rsp)
	movb	$122, 582(%rsp)
	movb	$48, 581(%rsp)
	movb	$49, 580(%rsp)
	movb	$50, 579(%rsp)
	movb	$51, 578(%rsp)
	movb	$52, 577(%rsp)
	movb	$53, 576(%rsp)
	movzbl	592(%rsp), %esi
	vmovd	%esi, %xmm0
	movzbl	593(%rsp), %esi
	vpinsrb	$1, %esi, %xmm0, %xmm0
	movzbl	594(%rsp), %esi
	vpinsrb	$2, %esi, %xmm0, %xmm0
	movzbl	595(%rsp), %esi
	vpinsrb	$3, %esi, %xmm0, %xmm0
	movzbl	596(%rsp), %esi
	vpinsrb	$4, %esi, %xmm0, %xmm0
	movzbl	597(%rsp), %esi
	vpinsrb	$5, %esi, %xmm0, %xmm0
	movzbl	598(%rsp), %esi
	vpinsrb	$6, %esi, %xmm0, %xmm0
	movzbl	599(%rsp), %esi
	vpinsrb	$7, %esi, %xmm0, %xmm0
	movzbl	600(%rsp), %esi
	vpinsrb	$8, %esi, %xmm0, %xmm0
	movzbl	601(%rsp), %esi
	vpinsrb	$9, %esi, %xmm0, %xmm0
	movzbl	602(%rsp), %esi
	vpinsrb	$10, %esi, %xmm0, %xmm0
	movzbl	603(%rsp), %esi
	vpinsrb	$11, %esi, %xmm0, %xmm0
	movzbl	604(%rsp), %esi
	vpinsrb	$12, %esi, %xmm0, %xmm0
	movzbl	605(%rsp), %esi
	vpinsrb	$13, %esi, %xmm0, %xmm0
	movzbl	606(%rsp), %esi
	vpinsrb	$14, %esi, %xmm0, %xmm0
	movzbl	607(%rsp), %esi
	vpinsrb	$15, %esi, %xmm0, %xmm0
	movzbl	576(%rsp), %esi
	vmovd	%esi, %xmm1
	movzbl	577(%rsp), %esi
	vpinsrb	$1, %esi, %xmm1, %xmm1
	movzbl	578(%rsp), %esi
	vpinsrb	$2, %esi, %xmm1, %xmm1
	movzbl	579(%rsp), %esi
	vpinsrb	$3, %esi, %xmm1, %xmm1
	movzbl	580(%rsp), %esi
	vpinsrb	$4, %esi, %xmm1, %xmm1
	movzbl	581(%rsp), %esi
	vpinsrb	$5, %esi, %xmm1, %xmm1
	movzbl	582(%rsp), %esi
	vpinsrb	$6, %esi, %xmm1, %xmm1
	movzbl	583(%rsp), %esi
	vpinsrb	$7, %esi, %xmm1, %xmm1
	movzbl	584(%rsp), %esi
	vpinsrb	$8, %esi, %xmm1, %xmm1
	movzbl	585(%rsp), %esi
	vpinsrb	$9, %esi, %xmm1, %xmm1
	movzbl	586(%rsp), %esi
	vpinsrb	$10, %esi, %xmm1, %xmm1
	movzbl	587(%rsp), %esi
	vpinsrb	$11, %esi, %xmm1, %xmm1
	movzbl	588(%rsp), %esi
	vpinsrb	$12, %esi, %xmm1, %xmm1
	movzbl	589(%rsp), %esi
	vpinsrb	$13, %esi, %xmm1, %xmm1
	movzbl	590(%rsp), %esi
	vpinsrb	$14, %esi, %xmm1, %xmm1
	movzbl	591(%rsp), %esi
	vpinsrb	$15, %esi, %xmm1, %xmm1
                                        ## implicit-def: %ymm9
	vmovaps	%xmm1, %xmm9
	vinserti128	$1, %xmm0, %ymm9, %ymm9
	vmovdqa	%ymm9, 544(%rsp)
	vmovdqa	544(%rsp), %ymm9
	vmovdqa	%ymm9, 352(%rsp)
	movq	328(%rsp), %rcx         ## 8-byte Reload
	movq	%rcx, 344(%rsp)
	movq	344(%rsp), %rcx
	movsbl	(%rcx), %esi
	movq	344(%rsp), %rcx
	movsbl	1(%rcx), %edx
	movq	344(%rsp), %rcx
	movsbl	2(%rcx), %ecx
	movq	344(%rsp), %rdi
	movsbl	3(%rdi), %r8d
	movq	344(%rsp), %rdi
	movsbl	4(%rdi), %r9d
	movq	344(%rsp), %rdi
	movsbl	5(%rdi), %r10d
	movq	344(%rsp), %rdi
	movsbl	6(%rdi), %r11d
	movq	344(%rsp), %rdi
	movsbl	7(%rdi), %ebx
	movq	344(%rsp), %rdi
	movsbl	8(%rdi), %r14d
	movq	344(%rsp), %rdi
	movsbl	9(%rdi), %r15d
	movq	344(%rsp), %rdi
	movsbl	10(%rdi), %r12d
	movq	344(%rsp), %rdi
	movsbl	11(%rdi), %r13d
	movq	344(%rsp), %rdi
	movsbl	12(%rdi), %edi
	movl	%esi, 324(%rsp)         ## 4-byte Spill
	movq	344(%rsp), %rsi
	movsbl	13(%rsi), %esi
	movl	%esi, 320(%rsp)         ## 4-byte Spill
	movq	344(%rsp), %rsi
	movsbl	14(%rsi), %esi
	movl	%esi, 316(%rsp)         ## 4-byte Spill
	movq	344(%rsp), %rsi
	movsbl	15(%rsi), %esi
	movl	%esi, 312(%rsp)         ## 4-byte Spill
	movq	344(%rsp), %rsi
	movsbl	16(%rsi), %esi
	movl	%esi, 308(%rsp)         ## 4-byte Spill
	movq	344(%rsp), %rsi
	movsbl	17(%rsi), %esi
	movl	%esi, 304(%rsp)         ## 4-byte Spill
	movq	344(%rsp), %rsi
	movsbl	18(%rsi), %esi
	movl	%esi, 300(%rsp)         ## 4-byte Spill
	movq	344(%rsp), %rsi
	movsbl	19(%rsi), %esi
	movl	%esi, 296(%rsp)         ## 4-byte Spill
	movq	344(%rsp), %rsi
	movsbl	20(%rsi), %esi
	movl	%esi, 292(%rsp)         ## 4-byte Spill
	movq	344(%rsp), %rsi
	movsbl	21(%rsi), %esi
	movl	%esi, 288(%rsp)         ## 4-byte Spill
	movq	344(%rsp), %rsi
	movsbl	22(%rsi), %esi
	movl	%esi, 284(%rsp)         ## 4-byte Spill
	movq	344(%rsp), %rsi
	movsbl	23(%rsi), %esi
	movl	%esi, 280(%rsp)         ## 4-byte Spill
	movq	344(%rsp), %rsi
	movsbl	24(%rsi), %esi
	movl	%esi, 276(%rsp)         ## 4-byte Spill
	movq	344(%rsp), %rsi
	movsbl	25(%rsi), %esi
	movl	%esi, 272(%rsp)         ## 4-byte Spill
	movq	344(%rsp), %rsi
	movsbl	26(%rsi), %esi
	movl	%esi, 268(%rsp)         ## 4-byte Spill
	movq	344(%rsp), %rsi
	movsbl	27(%rsi), %esi
	movl	%esi, 264(%rsp)         ## 4-byte Spill
	movq	344(%rsp), %rsi
	movsbl	28(%rsi), %esi
	movl	%esi, 260(%rsp)         ## 4-byte Spill
	movq	344(%rsp), %rsi
	movsbl	29(%rsi), %esi
	movl	%esi, 256(%rsp)         ## 4-byte Spill
	movq	344(%rsp), %rsi
	movsbl	30(%rsi), %esi
	movl	%esi, 252(%rsp)         ## 4-byte Spill
	movq	344(%rsp), %rsi
	movsbl	31(%rsi), %esi
	movl	%esi, 248(%rsp)         ## 4-byte Spill
	movq	336(%rsp), %rsi         ## 8-byte Reload
	movl	%edi, 244(%rsp)         ## 4-byte Spill
	movq	%rsi, %rdi
	movl	324(%rsp), %esi         ## 4-byte Reload
	movl	%r10d, (%rsp)
	movl	%r11d, 8(%rsp)
	movl	%ebx, 16(%rsp)
	movl	%r14d, 24(%rsp)
	movl	%r15d, 32(%rsp)
	movl	%r12d, 40(%rsp)
	movl	%r13d, 48(%rsp)
	movl	244(%rsp), %r10d        ## 4-byte Reload
	movl	%r10d, 56(%rsp)
	movl	320(%rsp), %r10d        ## 4-byte Reload
	movl	%r10d, 64(%rsp)
	movl	316(%rsp), %r10d        ## 4-byte Reload
	movl	%r10d, 72(%rsp)
	movl	312(%rsp), %r10d        ## 4-byte Reload
	movl	%r10d, 80(%rsp)
	movl	308(%rsp), %r10d        ## 4-byte Reload
	movl	%r10d, 88(%rsp)
	movl	304(%rsp), %r10d        ## 4-byte Reload
	movl	%r10d, 96(%rsp)
	movl	300(%rsp), %r10d        ## 4-byte Reload
	movl	%r10d, 104(%rsp)
	movl	296(%rsp), %r10d        ## 4-byte Reload
	movl	%r10d, 112(%rsp)
	movl	292(%rsp), %r10d        ## 4-byte Reload
	movl	%r10d, 120(%rsp)
	movl	288(%rsp), %r10d        ## 4-byte Reload
	movl	%r10d, 128(%rsp)
	movl	284(%rsp), %r10d        ## 4-byte Reload
	movl	%r10d, 136(%rsp)
	movl	280(%rsp), %r10d        ## 4-byte Reload
	movl	%r10d, 144(%rsp)
	movl	276(%rsp), %r10d        ## 4-byte Reload
	movl	%r10d, 152(%rsp)
	movl	272(%rsp), %r10d        ## 4-byte Reload
	movl	%r10d, 160(%rsp)
	movl	268(%rsp), %r10d        ## 4-byte Reload
	movl	%r10d, 168(%rsp)
	movl	264(%rsp), %r10d        ## 4-byte Reload
	movl	%r10d, 176(%rsp)
	movl	260(%rsp), %r10d        ## 4-byte Reload
	movl	%r10d, 184(%rsp)
	movl	256(%rsp), %r10d        ## 4-byte Reload
	movl	%r10d, 192(%rsp)
	movl	252(%rsp), %r10d        ## 4-byte Reload
	movl	%r10d, 200(%rsp)
	movl	248(%rsp), %r10d        ## 4-byte Reload
	movl	%r10d, 208(%rsp)
	movl	%eax, 240(%rsp)         ## 4-byte Spill
	movb	$0, %al
	vzeroupper
	callq	_printf
	movq	___stack_chk_guard@GOTPCREL(%rip), %rdi
	movq	(%rdi), %rdi
	movq	640(%rsp), %rsi
	cmpq	%rsi, %rdi
	movl	%eax, 236(%rsp)         ## 4-byte Spill
	jne	LBB0_2
## %bb.1:
	xorl	%eax, %eax
	leaq	-40(%rbp), %rsp
	popq	%rbx
	popq	%r12
	popq	%r13
	popq	%r14
	popq	%r15
	popq	%rbp
	retq
LBB0_2:
	callq	___stack_chk_fail
	ud2
	.cfi_endproc
                                        ## -- End function
	.section	__TEXT,__const
	.p2align	4               ## @main.evens
l_main.evens:
	.long	1073741824              ## float 2
	.long	1082130432              ## float 4
	.long	1086324736              ## float 6
	.long	1090519040              ## float 8
	.long	1092616192              ## float 10
	.long	1094713344              ## float 12
	.long	1096810496              ## float 14
	.long	1098907648              ## float 16

	.section	__TEXT,__cstring,cstring_literals
L_.str:                                 ## @.str
	.asciz	"%f %f %f %f %f %f %f %f\n"

L_.str.1:                               ## @.str.1
	.asciz	"asciimessage: %c %c %c %c %c %c %c %c %c %c %c %c %c %c %c %c %c %c %c %c %c %c %c %c %c %c %c %c %c %c %c %c \n"


.subsections_via_symbols
