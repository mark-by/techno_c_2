#include <sys/sysinfo.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <math.h>

void start_processes( int amount, int * counter) {
    int * shareable_var = mmap(NULL, sizeof(int),
                               PROT_READ|PROT_WRITE, MAP_SHARED|MAP_ANONYMOUS, -1, 0);
    *shareable_var = 0;
    *counter = 0;
    int pid;
    int num_of_forks = ceil( log2( amount ) );
    for (int i = 0; i < num_of_forks; i++) {
        pid = fork();
        if (pid == 0) {
            if (*shareable_var < amount - 1) {
                *shareable_var += 1;
                *counter = *shareable_var;
            } else {
                exit(0);
            }
        }
    }
}

long get_file_size( const char* filename ) {
    FILE * file = fopen( filename, "r");
    fseek(file, 0, SEEK_END);
    long result = ftell(file);
    fclose(file);
    return result;
}

int count_symbol_in_file(const char symbol, char* file, long file_size) {
    int counter = 0;
    for (int i = 0; i < file_size; i++) {
        if (file[i] == symbol) {
            counter++;
        }
    }
    return counter;
}

char * put_file_in_memory(const char* file_name, long file_size) {
    int fd = open(file_name, O_RDONLY);
    char * file = mmap(NULL, file_size, PROT_READ, MAP_FILE|MAP_SHARED, fd, 0);
    close(fd);
    return file;
}
