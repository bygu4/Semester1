#pragma once
#pragma execution_character_set("utf-8")

// чтение массива из файла. Считывает размер массива, затем сам массив
// принимает имя файла и указатель, по которому записывает размер считанного массива
int* readArrayFromFile(const char* const nameOfFile, int* const sizeOfArray);
