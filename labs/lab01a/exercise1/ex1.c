#include <string.h>
#include "ex1.h"

/* Returns the number of times LETTER appears in STR.
There are two different ways to iterate through a string.
1st way hint: strlen() may be useful
2nd way hint: all strings end in a null terminator */
int num_occurrences(char *str, char letter) {
    /* TODO: implement num_occurances */
    int times, len, i;
    times = 0;
    len = strlen(str);
    for (i = 0; i < len; ++i) {
        if (str[i] == letter)
            ++times;
    }
    return times;
}

/* Populates DNA_SEQ with the number of times each nucleotide appears.
Each sequence will end with a NULL terminator and will have up to 20 nucleotides.
All letters will be upper case. */
void compute_nucleotide_occurrences(DNA_sequence *dna_seq) {
    /* TODO: implement compute_nucleotide_occurances */
    char *str = dna_seq->sequence;
    dna_seq->A_count = num_occurrences(str, 'A');
    dna_seq->C_count = num_occurrences(str, 'C');
    dna_seq->G_count = num_occurrences(str, 'G');
    dna_seq->T_count = num_occurrences(str, 'T');
    return;
}
