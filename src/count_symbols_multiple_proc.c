#include <stdio.h>
#include <string.h>
#include <sys/wait.h>
#include "count_symbols/count_symbols.h"


void count_symbols(FILE * out, const char * symbols, const char * file_name) {
    long file_size = get_file_size(file_name);
    char * file = put_file_in_memory(file_name, file_size);
    int rel_pid = 0;
    int num_proc = strlen(symbols);
    start_processes(num_proc, &rel_pid);
    const char symbol = symbols[rel_pid];
    int num_of_symbol = count_symbol(symbol, file, file_size);
    fprintf(out, "%c : %d\n", symbol, num_of_symbol);

    while (wait(NULL) > 0);
}
