#ifndef TLPI_HDR_H
#define TLPI_HDR_H // предотвращение двойного включения

#include <sys/types.h>

#include <stdio.h>
#include <stdlib.h>

#include <unistd.h> // прототипы системных вызовов
#include <errno.h> // константы ошибок
#include <string.h>
#include "get_num.h" // объявление наших функций для обработки числовых аргументов getInt() getLong()

#include "error_functions.h" // Объявление наших функкций обработки ошибок
typedef enum { FALSE, TRUE } Boolean;

#define min(m, n) ((m) < (n) ? (m) : (n))
#define max(m, n) ((m) > (n) ? (m) : (n))
#endif