#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

char* removeSpaces(const char* string)
{
    size_t sizeOfString = strlen(string);
    int charactersWithoutSpaces = 0;
    for (int i = 0; i < sizeOfString; ++i)
    {
        if (string[i] != ' ')
        {
            ++charactersWithoutSpaces;
        }
    }
    char* stringWithoutSpaces = (char*)calloc(charactersWithoutSpaces, sizeof(char));
    if (stringWithoutSpaces == NULL)
    {
        return NULL;
    }

    int i = 0;
    int count = 0;
    while (i < sizeOfString && count < charactersWithoutSpaces)
    {
        char character = string[i];
        if (character != ' ')
        {
            stringWithoutSpaces[count] = character;
            ++count;
        }
        ++i;
    }
    return stringWithoutSpaces;
}

bool isPalindrome(const char* string)
{
    char* stringWithoutSpaces = removeSpaces(string);
    if (stringWithoutSpaces == NULL)
    {
        return false;
    }
    size_t sizeOfString = strlen(stringWithoutSpaces);
    for (int i = 0; i < sizeOfString / 2; ++i)
    {
        if (stringWithoutSpaces[i] != stringWithoutSpaces[sizeOfString - i - 1])
        {
            free(stringWithoutSpaces);
            return false;
        }
    }
    free(stringWithoutSpaces);
    return true;
}

bool testOneIsPassed()
{
    char string[10] = { "olo lo lo\0" };
    return isPalindrome(string);
}

bool testTwoIsPassed()
{
    char string[2] = { "a\0" };
    return isPalindrome(string);
}

bool testThreeIsPassed()
{
    char string[8] = { "111 211\0" };
    return !isPalindrome(string);
}

bool testFourIsPassed()
{
    char string[] = { '\0' };
    return isPalindrome(string);
}

bool allTestsArePassed()
{
    return testOneIsPassed() && testTwoIsPassed() && testThreeIsPassed() && testFourIsPassed();
}

int main()
{
    if (!allTestsArePassed())
    {
        printf("An error occured");
        return -1;
    }
    char inputString[1024] = { '\0' };
    printf("Enter a string: ");
    scanf_s("%s", inputString, 1023);
    printf(isPalindrome(inputString) ? "This string is a palindrome" : "This string is not a palindrome");
}