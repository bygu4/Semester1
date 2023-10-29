#pragma once
#include <stdbool.h>

#define SUCCESS 0
#define BAD_ALLOCATION 1

// получить из стандартного потока число воинов и отсчет, вывести в консоль номера оставшихся воинов
// возвращает наличие ошибки при выделении памяти
bool console(void);
