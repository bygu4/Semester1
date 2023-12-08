#include "huffman.h"

int main(void)
{
    size_t resultSize = 0;
    char* result = compress("Hello world!", &resultSize);
    printf("%s\n", result);
}
