.globl read_matrix

.text
# ==============================================================================
# FUNCTION: Allocates memory and reads in a binary file as a matrix of integers
#
# FILE FORMAT:
#   The first 8 bytes are two 4 byte ints representing the # of rows and columns
#   in the matrix. Every 4 bytes afterwards is an element of the matrix in
#   row-major order.
# Arguments:
#   a0 (char*) is the pointer to string representing the filename
#   a1 (int*)  is a pointer to an integer, we will set it to the number of rows
#   a2 (int*)  is a pointer to an integer, we will set it to the number of columns
# Returns:
#   a0 (int*)  is the pointer to the matrix in memory
# Exceptions:
#   - If malloc returns an error,
#     this function terminates the program with error code 26
#   - If you receive an fopen error or eof,
#     this function terminates the program with error code 27
#   - If you receive an fclose error or eof,
#     this function terminates the program with error code 28
#   - If you receive an fread error or eof,
#     this function terminates the program with error code 29
# ==============================================================================
read_matrix:

	# Prologue
	addi sp, sp, -24
	sw ra, 0(sp)
	sw s0, 4(sp)
	sw s1, 8(sp)
	sw s2, 12(sp)
	sw s3, 16(sp)	# fd
	sw s4, 20(sp)	# matrix pointer

	mv s0, a0
	mv s1, a1 
	mv s2, a2

	# open file
	mv a0, s0
	li a1, 0	# read-only
	jal fopen
	li t0, -1
	beq t0, a0, error_fopen

	mv s3, a0	# save fd

	# read number of rows
	mv a0, s3
	mv a1, s1 
	li a2, 4
	addi sp, sp, -4
	sw a2, 0(sp)
	jal fread
	lw a2, 0(sp)
	addi sp, sp, 4
	bne a0, a2, error_fread

	# read number of colums
	mv a0, s3
	mv a1, s2 
	li a2, 4
	addi sp, sp, -4
	sw a2, 0(sp)
	jal fread
	lw a2, 0(sp)
	addi sp, sp, 4
	bne a0, a2, error_fread

	# malloc memory for matrix
	lw a1, 0(s1)
	lw a2, 0(s2)
	mul t1, a1, a2	# size of matrix
	slli t1, t1, 2
	addi sp, sp, -4
	sw t1, 0(sp)
	mv a0, t1
	jal malloc
	lw t1, 0(sp)
	addi sp, sp, 4
	beq a0, x0, error_malloc

	mv s4, a0	# matrix pointer

	# read matrix from file
	mv a0, s3 
	mv a1, s4
	mv a2, t1
	addi sp, sp, -4
	sw a2, 0(sp)
	jal fread
	lw a2, 0(sp)
	addi sp, sp, 4
	bne a0, a2, error_fread

	# close file
	mv a0, s3
	jal fclose
	li t0, 0
	bne a0, t0, error_fclose

	mv a0, s4

	# Epilogue
	lw ra, 0(sp)
	lw s0, 4(sp)
	lw s1, 8(sp)
	lw s2, 12(sp)
	lw s3, 16(sp)
	lw s4, 20(sp)
	addi sp, sp, 24

	ret

error_malloc:
	li a0, 26
	j exit

error_fopen:
	li a0, 27
	j exit

error_fclose:
	li a0, 28
	j exit

error_fread:
	li a0, 29
	j exit