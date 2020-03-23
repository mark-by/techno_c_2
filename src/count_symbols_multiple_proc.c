#include <stdio.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include "count_symbols/count_symbols.h"


void count_symbols(FILE * out, const char * symbols, const char * memory, long size) {
    int rel_pid = 0;
    int num_proc = strlen(symbols);
    int init_pid = getpid();
    start_processes(num_proc, &rel_pid);
    const char symbol = symbols[rel_pid];
    int num_of_symbol = count_symbol(symbol, memory, size);
    fprintf(out, "%c : %d\n", symbol, num_of_symbol);
    if (getpid() != init_pid) {
        while(wait(NULL) > 0);
        exit(0);
    }
    while (wait(NULL) > 0);
}
