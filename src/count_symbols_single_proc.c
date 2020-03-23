#include <stdio.h>
#include "count_symbols/count_symbols.h"

void count_symbols(FILE * out, const char * symbols, const char * memory, long size) {
    for (int i = 0; symbols[i] != '\0'; i++) {
        int num_of_symbol = count_symbol(symbols[i], memory, size);
        fprintf(out, "%c : %d\n", symbols[i], num_of_symbol);
    }
}