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

	# Prologue
	addi sp, sp, -20
	sw s0, 0(sp)
	sw s1, 4(sp)
	sw s2, 8(sp)
	sw s3, 12(sp)
	sw s4, 16(sp)

loop_start:
	add s0, a0, x0 # arr1
	add s1, a1, x0 # arr2
	add s2, a2, x0 # number of elements
	add s3, a3, x0 # stride of arr1
	add s4, a4, x0 # stride of arr2

	addi t0, x0, 1
	blt s2, t0, error_arr_len
	blt s3, t0, error_stride
	blt s4, t0, error_stride
	
	add t0, x0, x0 # nums
	add t1, x0, x0 # arr1 idx
	add t2, x0, x0 # arr2 idx
	add t3, x0, x0 # dot_sum
	j continue

error_arr_len:
	li a0, 36
	j exit
error_stride:
	li a0, 37
	j exit

continue:
	beq t0, s2, loop_end
	slli a1, t1, 2
	slli a2, t2, 2
	add a1, a1, s0 
	add a2, a2, s1
	lw a1, 0(a1)
	lw a2, 0(a2)
	mul a1, a1, a2
	add t3, t3, a1

	addi t0, t0, 1
	add t1, t1, s3
	add t2, t2, s4
	j continue

loop_end:

	add a0, t3, x0

	# Epilogue
	lw s0, 0(sp)
	lw s1, 4(sp)
	lw s2, 8(sp)
	lw s3, 12(sp)
	lw s4, 16(sp)
	addi sp, sp, 20
	ret
