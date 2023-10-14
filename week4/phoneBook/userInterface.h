#pragma once
#include "phonebook.h"

// добавление записи при работе с пользователем. Возвращает код ошибки
int addNoteUI(Phonebook* const phonebook);

// сохранение записей в файл при работе с пользователем. Возвращает код ошибки
int saveNotesToFileUI(const Phonebook* const phonebook, const char* const nameOfFile);

// вывести в консоль все считанные записи
void printAllNotes(const Phonebook* const phonebook);

// поиск номера по имени при работе с пользователем
void findNumberByNameUI(const Phonebook* const phonebook);

// поиск имени по номеру при работе с пользователем
void findNameByNumberUI(const Phonebook* const phonebook);
