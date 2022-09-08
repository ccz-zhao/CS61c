.globl relu

.text
# ==============================================================================
# FUNCTION: Performs an inplace element-wise ReLU on an array of ints
# Arguments:
#   a0 (int*) is the pointer to the array
#   a1 (int)  is the # of elements in the array
# Returns:
#   None
# Exceptions:
#   - If the length of the array is less than 1,
#     this function terminates the program with error code 36
# ==============================================================================
relu:
	# Prologue
	addi sp, sp, 4
    sw s0, 0(sp)
loop_start:
	add s0, a0, x0
    add t0, a1, x0
    bgt t0, x0, loop_continue
    li a0, 36
    j exit

loop_continue:
	beq t0, x0, loop_end
	addi t0, t0, -1
    

loop_end:


	# Epilogue


	ret
