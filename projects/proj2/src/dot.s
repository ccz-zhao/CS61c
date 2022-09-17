.globl dot

.text
# =======================================================
# FUNCTION: Dot product of 2 int arrays
# Arguments:
#   a0 (int*) is the pointer to the start of arr0
#   a1 (int*) is the pointer to the start of arr1
#   a2 (int)  is the number of elements to use
#   a3 (int)  is the stride of arr0
#   a4 (int)  is the stride of arr1
# Returns:
#   a0 (int)  is the dot product of arr0 and arr1
# Exceptions:
#   - If the length of the array is less than 1,
#     this function terminates the program with error code 36
#   - If the stride of either array is less than 1,
#     this function terminates the program with error code 37
# =======================================================
dot:
	# check length and stride
	li t0, 1
	blt a2, t0, exit_bad_len
	blt a3, t0, exit_bad_strid
	blt a4, t0, exit_bad_strid

	# Prologue
	li t0, 0	# curr_idx
	li t1, 0	# product

loop_start:
	beq t0, a2, loop_end
	mul t2, t0, a3
	mul t3, t0, a4
	slli t2, t2, 2
	slli t3, t3, 2
	add t2, t2, a0 
	add t3, t3, a1
	lw t2, 0(t2)
	lw t3, 0(t3)
	mul t2, t2, t3
	add t1, t1, t2

	addi t0, t0, 1
	j loop_start

loop_end:
	mv a0, t1
	# Epilogue
	ret

exit_bad_len:
	li a0, 36
    j exit

exit_bad_strid:
	li a0, 37
	j exit