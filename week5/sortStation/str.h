#pragma once
#include <string.h>
#include <stdbool.h>

#define SUCCESS 0
#define BAD_ALLOCATION 1

typedef struct {
    char* data;
    size_t length;
    size_t capacity;
} String;

// инициализация строки
String* createString(const char* const data);

// очистить память, выделенную под строку. Обнуляет указатель
void freeString(String** const string);

// считать посимвольно строку произвольной длины из консоли
String* getString(const char breakPoint);

// добавить символ к строке. Возвращает код ошибки
int addCharToString(String* const string, const char character);

// проверить строки на равенство
bool stringsAreEqual(const char* const string1, const char* const string2);
