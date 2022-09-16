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
	addi sp, sp, -8
    sw s0, 0(sp)
	sw s1, 4(sp)
loop_start:
	add s0, a0, x0
    add s1, a1, x0
    bgt s1, x0, loop_continue
    li a0, 36
    j exit

loop_continue:
	beq s1, x0, loop_end
	addi s1, s1, -1
	lw t1, 0(s0)
	blt t1, x0, neg
continue:
	addi t0, x0, 1
	slli t0, t0, 2
	add s0, s0, t0
	j loop_continue
neg:
	add t1, x0, x0
	sw t1, 0(s0)
	j continue
    

loop_end:
	# Epilogue
	lw s0, 0(sp)
	lw s1, 4(sp)
	addi sp, sp, 8
	jr ra