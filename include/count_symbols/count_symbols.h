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

/*
 * Функция возвращает размер файла в байтах
 *
 * filename - путь к файлу
 */
long get_file_size( const char* filename );

/*
 * Функция загружает файл в память
 *
 * file_name - путь к файлу
 * file_size - размер файла
 */
char * put_file_in_memory(const char* file_name, long file_size);

/*
    Функция считает количество вхождений указанного символа в файл

    symbol - искомый символ
    file - указатель на область загруженного в память файл
    file_size - размер файла
*/
int count_symbol(char symbol, const char* file, long file_size);

/*
 *  Функция считает количество вхождений в указанной области памяти
 *  для каждого символа и результат выводит в out
 */
void count_symbols(FILE * out, const char * symbols, const char * memory, long size);
#endif