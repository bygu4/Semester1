#pragma once
#include <string.h>

#define MAX_NOTES 100
#define SIZE_OF_BUFFER 64
#define SUCCESS 0
#define BAD_ALLOCATION 1
#define FILE_NOT_FOUND 2
#define TOO_MUCH_NOTES 3

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

// чтение записей из файла. Ожидаемый формат: имя номер. Возвращает код ошибки
int readNotesFromFile(Phonebook* const phonebook, const char* const nameOfFile);

// сохранение записей из телефонной книги в файл. Формат: имя номер. Возвращает код ошибки
int saveNotesToFile(const Phonebook* const phonebook, const char* const nameOfFile);

// поиска номера по имени. Возвращает найденный номер, иначе NULL
char* findNumberByName(const Phonebook* const phonebook, const char* const nameToFind);

// поиск имени по номеру. Возвращает найденное имя, иначе NULL
char* findNameByNumber(const Phonebook* const phonebook, const char* const numberToFind);
