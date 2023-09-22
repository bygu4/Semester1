#include <stdio.h>
#include <string.h>
#include <stdbool.h>

int main()
{
    char string[256] = { '\0' };
    char substring[256] = { '\0' };
    printf("Enter string s (255 characters max): ");
    scanf_s("%s", string, 255);
    printf("Enter substring s1 (255 characters max): ");
    scanf_s("%s", substring, 255);

    const size_t lengthOfString = strlen(string);
    const size_t lengthOfSubstring = strlen(substring);
    int numberOfEntries = 0;
    for (int i = 0; i <= lengthOfString - lengthOfSubstring; ++i)
    {
        bool match = true;
        for (int j = 0; j < lengthOfSubstring; ++j)
        {
            if (string[i + j] != substring[j])
            {
                match = false;
                break;
            }
        }
        if (match)
        {
            ++numberOfEntries;
        }
    }
    printf("Number of entries: %d", numberOfEntries);
}