# Mike Hanling
###################
# The data segment
###################		
.data

# Create some null terminated strings to use
strWelcome:      .asciiz "Welcome to Midn. Hanling's Lab #1\n"
strGetN:         .asciiz "Number of times to run:"
strGetOp:        .asciiz "Please enter the x:"
strResultAdd:	 .asciiz "x + 5 is " 
strResultDouble: .asciiz "x + x is " 
strResultMult:   .asciiz "x * 8 is "
strClose:        .asciiz "Thank you for using Midn. Hanling's Lab #1\n"
strDone:	 .asciiz "DONE\n" 	 
strCR:		 .asciiz "\n" 
	
##########################################
# The text segment -- instructions go here
##########################################	
.text
		.globl main
main:
                # STEP 1 -- Welcome and get N
                li $v0, 4 # syscall 4 will print string whose address is in $a0
		la $a0, strWelcome      # "load address" of welcome statememt
		syscall     # actually print the string  

                #Get N times to run loop
                li $v0, 4     #syscall 4 for print string
                la $a0, strGetN
                syscall       #print the prompt
                li $v0, 5     #syscall 5 for read int
                syscall       #get N
                move $s1, $v0 #save N for later


                ### LOOP ###

LOOP:
                # CONDITIONAL
                beq $s1, $zero, CLOSE   #so long as N != 0, do loop

                # STEP 1 -- Get operand
                li $v0, 4
                la $a0, strGetOp       # Load the prompt
                syscall     # actually print prompt
                # Now read in the first operand 
		li $v0, 5      # syscall number 5 will read an int
		syscall        # actually read the int
		move $s0, $v0  # save result in $s0 for later
                
		# STEP 2 -- print the sum
                # First print the string prelude  
		li $v0, 4      # syscall number 4 -- print string
	        la $a0, strResultAdd   
	        syscall        # actually print the string   
	        # Then print the actual sum
	        li $v0, 1         # syscall number 1 -- print int
	        addi $a0, $s0, 5 # add 5 to operand
	        syscall           # actually print the int
		# Finally print a carriage return
		li $v0, 4      # syscall for print string
	        la $a0, strCR  # address of string with a carriage return
	        syscall        # actually print the string
		       
		# STEP 3 -- print the double
                # First print the string prelude  
		li $v0, 4      # syscall number 4 -- print string
	        la $a0, strResultDouble
	        syscall        # actually print the string  
	        # Then print the actual sum
	        li $v0, 1         # syscall number 1 -- print int
	        add $a0, $s0, $s0 # add our operand to itself
	        syscall           # actually print the string
		# Finally print a carriage return
		li $v0, 4      # syscall for print string
	        la $a0, strCR
	        syscall

		# STEP 4 -- print the mult
                # First print the string prelude  
		li $v0, 4      # syscall number 4 -- print string
	        la $a0, strResultMult
	        syscall        # actually print the string  
	        # Then print the actual sum
	        li $v0, 1         # syscall number 1 -- print int
	        sll $a0, $s0, 3   # mult by 8
	        syscall           # actually print the string
		# Finally print a carriage return
		li $v0, 4      # syscall for print string
	        la $a0, strCR
	        syscall

                # DECEMENT N and loop
                addi $s1, $s1, -1
                j LOOP


CLOSE:
                # STEP 5 -- Print the closing
                li $v0, 4     # system call 4 -- print string
                la $a0, strClose
                syscall       #actaully print string

		# STEP 6 -- exit
		li $v0, 10  # Syscall number 10 is to terminate the program
		syscall     # exit now

