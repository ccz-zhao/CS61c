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
	# check to see if the length of the array is less than 1
	li t0, 1
	blt a1, t0, exit_bad_len
	# Prologue
	add t0, x0, x0 # t0 is the loop index "i"
loop_start:
	beq a1, t0, loop_end
	slli t3, t0, 2
	add t1, t3, a0
	lw t2, 0(t1)
	addi t0, t0, 1
	bgt t2, x0, loop_start

	sw x0, 0(t1)
	j loop_start

loop_end:
	# Epilogue
	ret

exit_bad_len:
	li a0, 36
    j exit