#include <stdio.h>
#include <count_symbols/count_symbols.h>

int main(int args, char ** argv) {
    if (args != 3) {
        printf("Usage: <symbols> <file_path>");
    }

    count_symbols(stdout, argv[1], argv[2]);
    return 0;
}
