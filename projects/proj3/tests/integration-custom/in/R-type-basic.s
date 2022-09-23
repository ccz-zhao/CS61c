addi t0, x0, 100
addi t1, x0, -1
add t1, t0, x0
add t1, t0, t1
mul s0, t1, t1
sub s1, s0, t1
addi t1, x0, 2
sll s2, s1, t1
xor s3, s2, s1
srl s4, t1, t1
sra s5, s3, t1
or t0, s5, s3
and t1, s5, s3
mulhu t1, s5, s3
mulh t1, s5, s3

