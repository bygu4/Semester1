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

// вспомогательная функция для добавления записи, нужна для тестов
int addNoteSupport(Phonebook* const phonebook, const char* const name, const char* const number);

// добавление записи при работе с пользователем
int addNote(Phonebook* const phonebook);

// чтение имени и номера из файла. Ожидаемый формат: имя номер
int readNotesFromFile(Phonebook* const phonebook, const char* const nameOfFile);

// вспомогательная функция для сохранения записей в файл, нужна для тестов
// формат: имя номер
int saveNotesToFileSupport(const Phonebook* const phonebook, const char* const nameOfFile);

// сохранение записей в файл при работе с пользователем
int saveNotesToFile(const Phonebook* const phonebook, const char* const nameOfFile);

// вывести в консоль все считанные записи
void printAllNotes(const Phonebook* const phonebook);

// вспомогательная функция для поиска номера по имени, нужна для тестов
char* findNumberByNameSupport(const Phonebook* const phonebook, const char* const nameToFind);

// поиск номера по имени при работе с пользователем
void findNumberByName(const Phonebook* const phonebook);

// вспомогательная функция для поиска имени по номеру, нужна для тестов
char* findNameByNumberSupport(const Phonebook* const phonebook, const char* const numberToFind);

// поиск имени по номеру при работе с пользователем
void findNameByNumber(const Phonebook* const phonebook);
