#include <stdio.h>
#include "count_symbols/count_symbols.h"

void count_symbols(FILE * out, const char * symbols, const char * file_name) {
    long file_size = get_file_size(file_name);
    char * file = put_file_in_memory(file_name, file_size);
    for (int i = 0; symbols[i] != '\0'; i++) {
        int num_of_symbol = count_symbol(symbols[i], file, file_size);
        fprintf(out, "%c : %d\n", symbols[i], num_of_symbol);
    }
}