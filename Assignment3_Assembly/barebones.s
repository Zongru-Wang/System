# Build an executable using the following:
#
# clang barebones.s -o barebones  # clang is another compiler like gcc
#
.text
_barebones:

.data
	
.globl main

main:
					# (1) What are we setting up here?
					# Ans: Set up the stack, make the stack pointer 
	pushq %rbp			# points to the base pointer. And call sys_write to print out the message.
	movq  %rsp, %rbp		# The whole main funtion will print out the message "Hello World!"

					
                                        # (2) What is going on here
					# Ans:first call sys_write and stdout  
	movq $1, %rax			# let it write the data in the memory to the console.
	movq $1, %rdi			#move the .heloo.str to %rsi for the later print
	leaq .hello.str,%rsi		#


					# (3) What is syscall? We did not talk about this
					# in class.
					# Ans: it is a call to a funtion biult into the operation sysytem.
	syscall				# Which syscall is being run?
					# Ans: sys_write

					# (4) What would another option be instead of 
					# using a syscall to achieve this?
					# Ans:int 0x88

	movq	$60, %rax		# (5) We are again setting up another syscall
	movq	$0, %rdi		# What command is it?
					# Ans:	sys_exit
	syscall

	popq %rbp			# (Note we do not really need
					# this command here after the syscall)

.hello.str:
	.string "Hello World!\n"
	.size	.hello.str,13		# (6) Why is there a 13 here?
					# Ans: The size of the things we print is 13 length.	
