#pragma once

// возвращает массив: двоичное представление переданного int
char* createBinaryRepresentation(const int number);

// сложение столбиком двоичных представлений
char* binaryAddition(const char* const binaryRepresentation1, const char* const binaryRepresentation2);

// переводит двоичное представление в int
int binaryToDecimal(const char* const binaryRepresentation);
