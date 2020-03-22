#include <stdio.h>
#include <string.h>
#include <sys/wait.h>
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
    int rel_pid = 0;
    int num_proc = strlen(symbols);
    start_processes(num_proc, &rel_pid);
    const char symbol = symbols[rel_pid];
    int num_of_symbol = count_symbol_in_file(symbol, file, file_size);
    printf("%c : %d\n", symbol, num_of_symbol);

    while (wait(NULL) > 0);
    return 0;
}
