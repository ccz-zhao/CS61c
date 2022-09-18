.globl write_matrix

.text
# ==============================================================================
# FUNCTION: Writes a matrix of integers into a binary file
# FILE FORMAT:
#   The first 8 bytes of the file will be two 4 byte ints representing the
#   numbers of rows and columns respectively. Every 4 bytes thereafter is an
#   element of the matrix in row-major order.
# Arguments:
#   a0 (char*) is the pointer to string representing the filename
#   a1 (int*)  is the pointer to the start of the matrix in memory
#   a2 (int)   is the number of rows in the matrix
#   a3 (int)   is the number of columns in the matrix
# Returns:
#   None
# Exceptions:
#   - If you receive an fopen error or eof,
#     this function terminates the program with error code 27
#   - If you receive an fclose error or eof,
#     this function terminates the program with error code 28
#   - If you receive an fwrite error or eof,
#     this function terminates the program with error code 30
# ==============================================================================
write_matrix:

	# Prologue
	addi sp, sp, -28
	sw ra, 0(sp)
	sw s0, 4(sp)
	sw s1, 8(sp)
	sw s2, 12(sp)
	sw s3, 16(sp)
	sw s4, 20(sp)	# fd
	sw s5, 24(sp) 	# int*

	mv s0, a0
	mv s1, a1 
	mv s2, a2 
	mv s3, a3

	# open file
	mv a0, s0 
	li a1, 1	# write only
	jal fopen 
	li t0, -1
	beq a0, t0, error_fopen

	mv s4, a0 	# save fd

	# malloc memory for nums
	li a0, 4	# int 4 bytes
	jal malloc
	beq a0, x0, error_malloc

	mv s5, a0 	# save int*

	# write number of rows
	sw s2, 0(s5)
	mv a0, s4
	mv a1, s5
	li a2, 1
	li a3, 4
	addi sp, sp, -4
	sw a2, 0(sp)
	jal fwrite
	lw a2, 0(sp)
	addi sp, sp 4
	bne a0, a2, error_fwrite

	# write number of columns
	sw s3, 0(s5)
	mv a0, s4
	mv a1, s5
	li a2, 1
	li a3, 4
	addi sp, sp, -4
	sw a2, 0(sp)
	jal fwrite
	lw a2, 0(sp)
	addi sp, sp 4
	bne a0, a2, error_fwrite

	# write elements
	mul t0, s2, s3 
	mv a0, s4
	mv a1, s1 
	mv a2, t0
	li a3, 4
	addi sp, sp, -4
	sw a2, 0(sp)
	jal fwrite
	lw a2, 0(sp)
	addi sp, sp 4
	bne a0, a2, error_fwrite
	
	# close file
	mv a0, s4
	jal fclose
	li t0, 0
	bne a0, t0, error_fclose

	# free int*
	mv a0, s5
	jal free

	# Epilogue	
	lw ra, 0(sp)
	lw s0, 4(sp)
	lw s1, 8(sp)
	lw s2, 12(sp)
	lw s3, 16(sp)
	lw s4, 20(sp)	
	lw s5, 24(sp) 	
	addi sp, sp, 28

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

error_fwrite:
	li a0, 30
	j exit