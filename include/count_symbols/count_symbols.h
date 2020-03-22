#ifndef _COUNT_SYMBOLS_H_
#define _COUNT_SYMBOLS_H_
/*
   Функция запускает указанное количество (amount) процессов с присвоением
   в переменную counter id для каждого процесса

   amount - количество запускаемых процессов
   counter - переменная, в которую записывается id процесса (не pid,
   а порядковый номер 0, 1, 2 ....)
 */
void start_processes( int amount, int * counter);

long get_file_size( const char* filename );

char * put_file_in_memory(const char* file_name, long file_size);
/*
    Функция считает количество вхождений каждого символа в файл в соответствующей
    процессу области памяти. Массив symbol_counter - массив счетчиков, где
    позиция счетчика соответствует определенному символу

    file - указатель на shared memory считываемого файла
    symbol_counters - массив из 256 счетчиков (shared memory)
    rel_proc_id - относительный id процесса
*/
int count_symbol_in_file(const char symbol, char* file, long file_size);



#endif
