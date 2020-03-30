#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <time.h>

#define NUM_START 3
#define TEST_SYMBOLS "qwertyuiopasdfghjklzxcvbnm"

double test(const char * path, const char * symbols, const char * file, int num_start){
    struct timespec start, finish;
    double elapsed;
    int pid;
    clock_gettime(CLOCK_MONOTONIC, &start);
    for (int i = 0; i < num_start; i++) {
        pid = fork();
        if (pid == 0) {
            execl(path, " ", symbols, file, (char *) NULL);
            exit(0);
        } else {
            while(wait(NULL) > 0);
        }
    }
    clock_gettime(CLOCK_MONOTONIC, &finish);
    elapsed = (double)(finish.tv_sec - start.tv_sec)/num_start;
    return elapsed;
}

int main(int args, char ** argv) {
    if (args != 4) {
        printf("Usage: <prog_1> <prog_2> <test_file>\n");
        return 0;
    }
   double result_1 = test(argv[1], TEST_SYMBOLS, argv[3], NUM_START);
   double result_2 = test(argv[2], TEST_SYMBOLS, argv[3], NUM_START);
   printf("Result for %s: %f sec\n", argv[1], result_1);
   printf("Result for %s: %f sec\n", argv[2], result_2);
return 0;
}