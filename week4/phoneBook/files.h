#pragma once
#include "phonebook.h"

#define INITIAL_SIZE_OF_BUFFER 5 * sizeof(char)
#define FILE_NOT_FOUND 2
#define INCORRECT_FORMAT 5

// чтение записей из файла. Ожидаемый формат: имя номер. Возвращает код ошибки
int readNotesFromFile(Phonebook* const phonebook, const char* const nameOfFile);

// сохранение записей из телефонной книги в файл. Формат: имя номер. Возвращает код ошибки
int saveNotesToFile(const Phonebook* const phonebook, const char* const nameOfFile);
