.globl factorial

.data
n: .word 7

.text
main:
    la t0, n
    lw a0, 0(t0)
    jal ra, factorial

    addi a1, a0, 0
    addi a0, x0, 1
    ecall # Print Result

    addi a1, x0, '\n'
    addi a0, x0, 11
    ecall # Print newline

    addi a0, x0, 10
    ecall # Exit

factorial:
    # YOUR CODE HERE
    addi t0, x0, 1      # 0
    add t1, x0, a0      # curr_n = n, ret = n
loop:
    beq t1, t0, finish  # exit when curr_n = 1
    addi t1, t1, -1     # curr_n -= 1
    mul a0, a0, t1      # ret *= curr_n
    jal x0, loop

finish:
    jr ra
