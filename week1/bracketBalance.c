#include <stdio.h>
#include <stdbool.h>
#include <string.h>

bool checkBracketBalance(char* string, const size_t length)
{
    int count = 0;
    int i = 0;
    while (count >= 0 && i < length)
    {
        if (string[i] == '(')
        {
            count += 1;
        }
        if (string[i] == ')')
        {
            count -= 1;
        }
        ++i;
    }
    return count == 0 && i == length;
}

int main()
{
    char string[256] = { '\0' };
    printf("Enter a string with brackets (255 characters max): ");
    scanf_s("%s", string, 255);
    const size_t length = strlen(string);
    if (checkBracketBalance(string, length))
    {
        printf("Correct");
    }
    else
    {
        printf("Incorrect");
    }
}