#include <stdio.h>
#include <sys/sysinfo.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <math.h>
#include <string.h>
#include <sys/wait.h>

/*
   Функция запускает указанное количество (amount) процессов с присвоением
   в переменную counter для каждого процесса

   amount - количество запускаемых процессов
   shareable_var - int область shared memory (для подсчета процессов)
   counter - (not shared memory) переменная, в которую записывается
   относительный id процесса (номер процесса, относительно главного
   родительского, где главный родительский имеет id 0. Т.о. 10-ый процесс
   имеет id = 9)
 */
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

/* 
    Функция считает количество вхождений каждого символа в файл в соответствующей
    процессу области памяти. Массив symbol_counter - массив счетчиков, где
    позиция счетчика соответствует определенному символу

    file - указатель на shared memory считываемого файла
    symbol_counters - массив из 256 счетчиков (shared memory)
    rel_proc_id - относительный id процесса
*/
/* void count_symbols_in_region( int* symbol_counters, char* start, const char* end ) { */
    /* char * curr = start; */
    /* for (; curr != end; curr++) { */
        /* symbol_counters[*curr] += 1; */
    /* } */
/* } */

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

int main(int args, char** argv) {
    const char * symbols = argv[1];
    const char * file_name = argv[2];

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
