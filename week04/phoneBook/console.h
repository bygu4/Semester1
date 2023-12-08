#pragma once
#include "files.h"

// добавление записи при работе с пользователем. Возвращает код ошибки
int addNoteConsole(Phonebook* const phonebook);

// сохранение записей в файл при работе с пользователем. Возвращает код ошибки
int saveNotesToFileConsole(const Phonebook* const phonebook, const char* const nameOfFile);

// вывести в консоль все считанные записи
void printAllNotes(const Phonebook* const phonebook);

// поиск номера по имени при работе с пользователем. Возвращает код ошибки
int findNumberByNameConsole(const Phonebook* const phonebook);

// поиск имени по номеру при работе с пользователем. Возвращает код ошибки
int findNameByNumberConsole(const Phonebook* const phonebook);
