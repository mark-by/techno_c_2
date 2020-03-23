#include <stdio.h>
#include <count_symbols/count_symbols.h>

int main(int args, char ** argv) {
    if (args != 3) {
        printf("Usage: <symbols> <file_path>");
    }
    long file_size = get_file_size(argv[2]);
    char * file = put_file_in_memory(argv[2], file_size);
    count_symbols(stdout, argv[1], file, file_size);
    return 0;
}
