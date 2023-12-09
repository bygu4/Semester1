#pragma once
#include <string.h>

#define MAX_NOTES 100
#define SUCCESS 0
#define BAD_ALLOCATION 1
#define TOO_MUCH_NOTES 3
#define COPY_ERROR 4

typedef struct {
    char* name;
    char* number;
} Note;

typedef struct {
    Note* notes;
    size_t numberOfNotes;
} Phonebook;

// освободить память, выделенную под телефонную книгу. Обнуляет число записей
void freePhonebook(Phonebook* const phonebook);

// добавить запись в телефонную книгу. Возвращает код ошибки
int addNote(Phonebook* const phonebook, const char* const name, const char* const number);

// поиска номера по имени. Возвращает найденный номер, иначе NULL
char* findNumberByName(const Phonebook* const phonebook, const char* const nameToFind);

// поиск имени по номеру. Возвращает найденное имя, иначе NULL
char* findNameByNumber(const Phonebook* const phonebook, const char* const numberToFind);
