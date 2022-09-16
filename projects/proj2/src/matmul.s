.globl matmul

.text
# =======================================================
# FUNCTION: Matrix Multiplication of 2 integer matrices
#   d = matmul(m0, m1)
# Arguments:
#   a0 (int*)  is the pointer to the start of m0
#   a1 (int)   is the # of rows (height) of m0
#   a2 (int)   is the # of columns (width) of m0
#   a3 (int*)  is the pointer to the start of m1
#   a4 (int)   is the # of rows (height) of m1
#   a5 (int)   is the # of columns (width) of m1
#   a6 (int*)  is the pointer to the the start of d
# Returns:
#   None (void), sets d = matmul(m0, m1)
# Exceptions:
#   Make sure to check in top to bottom order!
#   - If the dimensions of m0 do not make sense,
#     this function terminates the program with exit code 38
#   - If the dimensions of m1 do not make sense,
#     this function terminates the program with exit code 38
#   - If the dimensions of m0 and m1 don't match,
#     this function terminates the program with exit code 38
# =======================================================
matmul:

	# Error checks
	addi t0, x0, 1
	blt a1, t0, error_38
	blt a4, t0, error_38
	blt a5, t0, error_38
	bne a2, a4, error_38
	# Prologue
	addi sp, sp, -32
	sw s0, 0(sp) 
	sw s1, 4(sp)
	sw s2, 8(sp)
	sw s3, 12(sp)
	sw s4, 16(sp)
	sw s5, 20(sp)
	sw s6, 24(sp)
	sw ra, 28(sp)

	add s0, a0, x0 # matA
	add s1, a1, x0 # rowA
	add s2, a2, x0 # colA
	add s3, a3, x0 # matB
	add s4, a4, x0 # rowB
	add s5, a5, x0 # colB
	add s6, a6, x0 # matC
	
	add t0, x0, x0 # i = 0
	add t1, x0, x0 # j = 0

	j outer_loop_start

error_38:
	li a0, 38
	j exit


outer_loop_start:
	beq t0, s1, outer_loop_end
	add t1, x0, x0

inner_loop_start:
	beq t1, s5, inner_loop_end # j == colB
	mul a0, s2, t0
	slli a0, a0, 2
	add a0, a0, s0 # dot start of arr0
	slli a1, t1, 2
	add a1, a1, s3 # dot start of arr1
	add a2, s2, x0 # num of element-> colA
	addi a3, x0, 1 # 1 stride of arr0
	add a4, s5, x0 # colB strides of arr1
	addi sp, sp, -8
	sw t0, 0(sp)
	sw t1, 4(sp)   # caller saved!!!!
	jal dot
	lw t0, 0(sp)
	lw t1, 4(sp)
	addi sp, sp, 8
	sw a0, 0(s6)   # send to matC
	addi s6, s6, 4

	addi t1, t1, 1
	j inner_loop_start
inner_loop_end:
	addi t0, t0, 1
	j outer_loop_start

outer_loop_end:

	# Epilogue
	lw s0, 0(sp) 
	lw s1, 4(sp)
	lw s2, 8(sp)
	lw s3, 12(sp)
	lw s4, 16(sp)
	lw s5, 20(sp)
	lw s6, 24(sp)
	lw ra, 28(sp)
	addi sp, sp, 32
	ret
