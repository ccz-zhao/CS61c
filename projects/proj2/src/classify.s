.globl classify

.text
# =====================================
# COMMAND LINE ARGUMENTS
# =====================================
# Args:
#   a0 (int)        argc
#   a1 (char**)     argv
#   a1[1] (char*)   pointer to the filepath string of m0
#   a1[2] (char*)   pointer to the filepath string of m1
#   a1[3] (char*)   pointer to the filepath string of input matrix
#   a1[4] (char*)   pointer to the filepath string of output file
#   a2 (int)        silent mode, if this is 1, you should not print
#                   anything. Otherwise, you should print the
#                   classification and a newline.
# Returns:
#   a0 (int)        Classification
# Exceptions:
#   - If there are an incorrect number of command line args,
#     this function terminates the program with exit code 31
#   - If malloc fails, this function terminates the program with exit code 26
#
# Usage:
#   main.s <M0_PATH> <M1_PATH> <INPUT_PATH> <OUTPUT_PATH>
classify:
	li t0, 5
	blt a0, t0, error_argc
	addi sp, sp, -52
	sw s0, 0(sp)	# argc
	sw s1, 4(sp)	# argv[]
	sw s2, 8(sp)	# mode
	sw s3, 12(sp)	# int* m0_row 	/ int * h_rows  / int * o
	sw s4, 16(sp)	# int* m0_col	/ int h_elements
	sw s5, 20(sp)	# int* m0_arr	/ int* o
	sw s6, 24(sp)	# int* m1_row 	/ int * o_rows
	sw s7, 28(sp)	# int* m1_col	/ int o_elements
	sw s8, 32(sp)	# int* m1_arr
	sw s9, 36(sp)	# int* input_row / int * h
	sw s10, 40(sp)	# int* input_col / int * h_cols / int * o_cols
	sw s11, 44(sp)	# int* input_arr
	sw ra, 48(sp)

	mv s0, a0
	mv s1, a1 
	mv s2, a2
ebreak
	# Read pretrained m0
	#	- malloc for rows and colums
	li a0, 4	# int 4 bytes
	jal malloc
	beq a0, x0, error_malloc
	mv s3, a0

	li a0, 4	# int 4 bytes
	jal malloc
	beq a0, x0, error_malloc
	mv s4, a0
	#	- call read_matrix
	lw a0, 4(s1)
	mv a1, s3
	mv a2, s4
	jal read_matrix
	mv s5, a0
ebreak
	# Read pretrained m1
	li a0, 4	# int 4 bytes
	jal malloc
	beq a0, x0, error_malloc
	mv s6, a0

	li a0, 4	# int 4 bytes
	jal malloc
	beq a0, x0, error_malloc
	mv s7, a0
	#	- call read_matrix
	lw a0, 8(s1)
	mv a1, s6
	mv a2, s7
	jal read_matrix
	mv s8, a0
ebreak
	# Read input matrix
	li a0, 4	# int 4 bytes
	jal malloc
	beq a0, x0, error_malloc
	mv s9, a0

	li a0, 4	# int 4 bytes
	jal malloc
	beq a0, x0, error_malloc
	mv s10, a0
	#	- call read_matrix
	lw a0, 12(s1)
	mv a1, s9
	mv a2, s10
	jal read_matrix
	mv s11, a0
ebreak
	# Compute h = matmul(m0, input)
	#	- malloc for h
	lw a0, 0(s3)	# m0_rows
	lw a1, 0(s10)	# input_cols
	mul a0, a0, a1
	mv t0, a0
	addi sp, sp, -4
	sw t0, 0(sp)
	slli a0, a0, 2
	jal malloc
	lw t0, 0(sp)
	addi sp, sp, 4
	beq a0, x0, error_malloc
	mv t1, a0		

	mv a0, s5
	lw a1, 0(s3)
	lw a2, 0(s4)
	mv a3, s11
	lw a4, 0(s9)
	lw a5, 0(s10)
	mv a6, t1

	addi sp, sp, -8
	sw t0, 0(sp)
	sw t1, 4(sp)
	jal matmul
	lw t0, 0(sp)
	lw t1, 4(sp)
	addi sp, sp, 8

	addi sp, sp, -8
	sw t0, 0(sp)
	sw t1, 4(sp)
	# 	-- free int* m0_cols
	mv a0, s4
	jal free 
	#	-- free int* input_rows
	mv a0, s9
	jal free 
	lw t0, 0(sp)
	lw t1, 4(sp)
	addi sp, sp, 8
	mv s4, t0	# now s4 is int h_elements
	mv s9, t1	# now s9 is int* h

ebreak
	# Compute h = relu(h)
	mv a0, s9
	mv a1, s4
	jal relu 
ebreak
	# Compute o = matmul(m1, h)
	#	- malloc for o
	lw a0, 0(s6)	# m1_rows
	lw a1, 0(s10)	# h_cols
	mul a0, a0, a1
	mv t0, a0
	addi sp, sp, -4
	sw t0, 0(sp)
	slli a0, a0, 2
	jal malloc
	lw t0, 0(sp)
	addi sp, sp, 4
	beq a0, x0, error_malloc
	mv t1, a0	

	mv a0, s8
	lw a1, 0(s6)
	lw a2, 0(s7)
	mv a3, s9
	lw a4, 0(s3)
	lw a5, 0(s10)
	mv a6, t1

	addi sp, sp, -8
	sw t0, 0(sp)
	sw t1, 4(sp)
	jal matmul
	lw t0, 0(sp)
	lw t1, 4(sp)
	addi sp, sp, 8

	addi sp, sp, -8
	sw t0, 0(sp)
	sw t1, 4(sp)
	# 	-- free int* m1_cols
	mv a0, s7
	jal free 
	#	-- free int* input_rows
	mv a0, s3
	jal free 
	lw t0, 0(sp)
	lw t1, 4(sp)
	addi sp, sp, 8
	mv s7, t0	# now s7 is int o_elements
	mv s3, t1	# now s3 is int* o
ebreak
	# Write output matrix o
	lw a0, 16(s1)
	mv a1, s3
	lw a2, 0(s6)
	lw a3, 0(s10)
	jal write_matrix
ebreak
	# Compute and return argmax(o)
	mv a0, s3
	mv a1, s7
	jal argmax

	mv s0, a0

	# If enabled, print argmax(o) and newline
	bne s2, x0, classify_end
	mv a0, s0
	jal print_int

	li a0, '\n'
	jal print_char

	# Epilogue
classify_end:
	mv a0, s3 
	jal free
	mv a0, s5
	jal free
	mv a0, s6
	jal free
	mv a0, s8
	jal free
	mv a0, s9 
	jal free
	mv a0, s10 
	jal free
	mv a0, s11
	jal free

	mv a0, s0

	lw s0, 0(sp)
	lw s1, 4(sp)
	lw s2, 8(sp)
	lw s3, 12(sp)
	lw s4, 16(sp)
	lw s5, 20(sp)
	lw s6, 24(sp)
	lw s7, 28(sp)
	lw s8, 32(sp)
	lw s9, 36(sp)
	lw s10, 40(sp)
	lw s11, 44(sp)
	lw ra, 48(sp)
	addi sp, sp, 52

	ret

error_malloc:
	li a0, 26
	j exit

error_argc:
	li a0, 31
	j exit