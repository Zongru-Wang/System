
# The add funtion and sub function works fine. 
# can get the uner input and do sub and add, but the user input should between 0 - 10
# If set the static value on the main funtion
# Use pushq $val, pushq $val can set up your own input value and comment out the line 104 in _add function.


# Failed to compare the user input for choosing which function to use,
# have to change between call _add and call _sub to swith the functions.

#Usage:
# gcc -c function.s
# ld funtion.o -o function
# ./function

# You will asked three inputs, But ignore the first input, it is for the function choose,
# But it doesn't work for now.
# The second and thrid inputs are useful, 
#If you have call _add in _start:. it will add your inputs

#If you modify the call _add to be call _sub
#It will make your   $firstinput - $second input
# Both add and sub function use user input can't  beyond 10.
# If you choose hard code(Set up values in main functions, it can deal with result beyond 10).


.welcome: 
          .ascii "Select an operation\12 1 - add\12 2 - substract\12"
.bss
    ds: .skip 8
    dsp: .skip 8

.global _start



.bss
    .lcomm buffer, 8
    .lcomm num1, 8
    .lcomm num2, 8

.text
_printWelcome: 
         movq $1, %rax
         movq $1, %rdi
         leaq .welcome, %rsi
         movq $44, %rdx
         syscall
         ret



_exit: 
     movq $60, %rax
     xor %rdi, %rdi
     syscall


# Read the user's choice
_read1: 
movq $0, %rax
movq $0, %rdi
movq $buffer, %rsi
movq $60, %rdx
syscall
ret

#Read the second input
_read2:
 movq $0, %rax
 movq $0, %rdi
 movq $num1, %rsi
 movq $60, %rdx
 syscall
 ret

#Read the third input
_read3:
 movq $0, %rax
 movq $0, %rdi
 movq $num2, %rsi
 movq $60, %rdx
 syscall
 ret

# Add function works good.
_add:
#prologue
pushq %rbp
movq %rsp, %rbp

push %rsi
push %rdi
push %rbx
subq $8, %rsp
movq 24(%rbp), %rbx
addq 16(%rbp), %rbx

movq %rbx, -32(%rbp)
movq -32(%rbp),%rax 

# Make it can deal with users input within 10.
# Comment it out if you want to use hard code value.
subq $5216, %rax

addq $8, %rsp
popq %rbx
popq %rdi
pop %rsi 
movq %rbp, %rsp

popq %rbp
ret

# Sub funtion works fine too.
_sub:
#prologue
pushq %rbp
movq %rsp, %rbp

push %rsi
push %rdi
push %rbx
subq $8, %rsp
movq 24(%rbp), %rbx
subq 16(%rbp), %rbx

movq %rbx, -32(%rbp)
movq -32(%rbp),%rax
addq $8, %rsp
popq %rbx
popq %rdi
popq %rsi 
movq %rbp, %rsp

popq %rbp
ret


# print the output after add or sub
_printOut:
   movq $ds, %rcx
   movq $10, %rbx
   movq %rbx, (%rcx)
   incq %rcx
   movq %rcx, dsp 

#Helper1
_printHelper:
   movq $0, %rdx
   movq $10, %rbx
   divq %rbx
   pushq %rax
   addq $48, %rdx
   
   movq dsp, %rcx
   mov %dl, (%rcx)
   incq %rcx
   movq %rcx, dsp 
   
   popq %rax
   cmpq $0, %rax
   jne _printHelper

#Helper2
_printHelper2:
   movq dsp, %rcx
   
   movq $1, %rax
   movq $1, %rdi
   movq %rcx, %rsi
   movq $1, %rdx
   syscall
  
   movq dsp, %rcx
   decq %rcx
   movq %rcx, dsp 
   
   cmpq $ds, %rcx
   jge _printHelper2
   ret



_start:
pushq %rbp
movq %rsp, %rbp

#Print the Welcome Message and aske user to choose functions.
call _printWelcome
   
call _read1
call _read2
call _read3


#You can set the num1 num2 to be hard code value if you want.
#If you are using the uer input can't beyond 10.
# Use hard code value is fine.
push num1
push num2


#Switch these two funtions if you like.
call  _add
#call _sub
call _printOut
call _exit
