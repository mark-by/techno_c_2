#include <stdio.h>
#include "count_symbols/count_symbols.h"


int main(int args, char** argv) {
    if (args != 3) {
        printf("Usage: <symbols> <filepath>\n");
        return 0;
    }
    const char *symbols = argv[1];
    const char *file_name = argv[2];

    long file_size = get_file_size(file_name);
    char * file = put_file_in_memory(file_name, file_size);
    for (int i = 0; symbols[i] != '\0'; i++) {
        int num_of_symbol = count_symbol_in_file(symbols[i], file, file_size);
        printf("%c : %d\n", symbols[i], num_of_symbol);
    }
    return 0;
}