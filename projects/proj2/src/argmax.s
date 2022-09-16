.globl argmax

.text
# =================================================================
# FUNCTION: Given a int array, return the index of the largest
#   element. If there are multiple, return the one
#   with the smallest index.
# Arguments:
#   a0 (int*) is the pointer to the start of the array
#   a1 (int)  is the # of elements in the array
# Returns:
#   a0 (int)  is the first index of the largest element
# Exceptions:
#   - If the length of the array is less than 1,
#     this function terminates the program with error code 36
# =================================================================
argmax:
	# Prologue
	addi sp, sp, -8
	sw s0, 0(sp)
	sw s1, 4(sp)

loop_start:
	add s0, a0, x0
	add s1, a1, x0
	add t0, x0, x0	# idx
	add t1, x0, x0	# max_idx
	add t2, x0, x0	# max
	add t4, s0, x0  # pointer
	bgt s1, x0, loop_continue
    li a0, 36
    j exit

loop_continue:
	beq s1, t0, loop_end
	lw t3, 0(t4)
	bgt t3, t2, greater
continue:
	addi t0, t0, 1
	slli t4, t0, 2
	add t4, s0, t4
	j loop_continue
greater:
	add t2, t3, x0
	add t1, t0, x0
	j continue


loop_end:
	add a0, t1, x0

	# Epilogue
	lw s0, 0(sp)
	lw s1, 4(sp)
	addi sp, sp, 8
	ret
