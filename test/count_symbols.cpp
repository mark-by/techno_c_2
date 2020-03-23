#include <gtest/gtest.h>
#include <cstdio>
#include <sys/mman.h>
#include <sys/wait.h>

extern "C" {
    #include "count_symbols/count_symbols.h"
}

TEST(CountSymbols, StartProcesses) {
    int amount = 10;
    int *shareable_array = static_cast<int *>(mmap(NULL, sizeof(int) * amount,
                                               PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0));
    int id;
    start_processes(amount, &id);
    shareable_array[id] = 1;
    while(wait(nullptr) > 0);
    for (int i = 0; i < amount; i++) {
        ASSERT_EQ(1, shareable_array[i]);
    }
}
