#include "binary.h"
#include <stdlib.h>

#define SIZE_OF_BINARY_REPRESENTATION sizeof(int) * 8

char* createBinaryRepresentation(const int number)
{
    char* binaryRepresentation = (char*)malloc(SIZE_OF_BINARY_REPRESENTATION);
    if (binaryRepresentation == NULL)
    {
        return NULL;
    }
    int bit = 1;
    for (size_t i = 0; i < SIZE_OF_BINARY_REPRESENTATION; ++i)
    {
        binaryRepresentation[SIZE_OF_BINARY_REPRESENTATION - i - 1] = number & bit ? 1 : 0;
        bit = bit << 1;
    }
    return binaryRepresentation;
}

char* binaryAddition(const char* const binaryRepresentation1, const char* const binaryRepresentation2)
{
    const size_t size = SIZE_OF_BINARY_REPRESENTATION;
    char* sum = (char*)malloc(size);
    if (sum == NULL)
    {
        free(sum);
        return NULL;
    }

    char transferBit = 0;
    for (size_t i = 0; i < size; ++i)
    {
        char sumOfDigits = binaryRepresentation1[size - i - 1] + binaryRepresentation2[size - i - 1] + transferBit;
        sum[size - i - 1] = sumOfDigits % 2;
        transferBit = sumOfDigits / 2;
    }
    return sum;
}

int binaryToDecimal(const char* const binaryRepresentation)
{
    int decimal = 0;
    if (binaryRepresentation[0] == 1)
    {
        decimal = pow(-2, SIZE_OF_BINARY_REPRESENTATION - 1);
    }
    for (size_t i = 0; i < SIZE_OF_BINARY_REPRESENTATION; ++i)
    {
        decimal += binaryRepresentation[i] << (SIZE_OF_BINARY_REPRESENTATION - i - 1);
    }
    return decimal;
}
