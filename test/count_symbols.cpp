#include <gtest/gtest.h>
#include <cstdio>
#include <sys/mman.h>
#include <sys/wait.h>
#include <unistd.h>

extern "C" {
    #include "count_symbols/count_symbols.h"
}

TEST(StartProcesses, CountProcesses) {
    int id;
    int init_pid = getpid();
    int amount = 100;
    int * shared_mem = static_cast<int *>(mmap(NULL, sizeof(int) * amount, PROT_READ | PROT_WRITE,
                                               MAP_SHARED | MAP_ANONYMOUS, -1, 0));
    start_processes(amount, &id);
    shared_mem[id] = 1;
    if (getpid() != init_pid) {
        while( wait(NULL) >0);
        exit(0);
    }
    while( wait(NULL) >0);
    for (int i = 0; i < amount; i++) {
        ASSERT_EQ(1, shared_mem[i]);
    }
}

TEST(GetFileSize, CorrectFileSize) {
    FILE * file;
    int sizes[] = {0, 10, 1000, 123423, 1235423};
    for (int i=0; i < 5; i++) {
        file = fopen("testfile", "w");
        rewind(file);
        for (int j=0; j < sizes[i]; j++) {
            fprintf(file, "%c", 'a');
        }
        fclose(file);
        file = fopen("testfile", "r");
        ASSERT_EQ(sizes[i], get_file_size("testfile"));
        fclose(file);
    }
}

TEST(CountSymbol, CorrectCountSymbol) {
    char symbols[1024] = {0};
    for (int i = 0; i < 1024; i += 2) {
        symbols[i] = 'b';
    }
    ASSERT_EQ(512, count_symbol('b', symbols, 1024));
}

TEST(CountSymbols, CorrectCountSymbols) {
    const char * symbols = "qwerty";
    std::string symbols_str(symbols);
    const int amounts[] = {20, 50, 100, 150, 234, 563};
    FILE * file = fopen("testfile", "w");
    for (int i = 0; symbols[i]!= '\0'; i++ ) {
        for (int j=0; j < amounts[i]; j++) {
            fprintf(file, "%c", symbols[i]);
        }
    }
    fclose(file);
    int file_size = 0;
    for (int i = 0; symbols[i] != '\0'; i++) {
        file_size += amounts[i];
    }
    char * testfile = put_file_in_memory("testfile", file_size);
    FILE * out = fopen("out", "w");
    count_symbols(out, symbols, testfile, file_size);
    fclose(out);
    out = fopen("out", "r");
    char c;
    int count;
    int pos;
    while(fscanf(out, "%c : %d", &c, &count) != EOF) {
        pos = symbols_str.find(c);
        if (pos >= 0) {
            ASSERT_EQ(count, amounts[pos]);
        }
    }
    fclose(out);
}
