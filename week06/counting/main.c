#include "console.h"
#include "test.h"
#include <stdio.h>

static bool stringsAreEqual(const char* const string1, const char* const string2)
{
    for (size_t i = 0; string1[i] != '\0' || string2[i] != '\0'; ++i)
    {
        if (string1[i] != string2[i])
        {
            return false;
        }
    }
    return true;
}

int main(const unsigned int argc, const char* const argv[])
{
    const bool allTestsArePassed = test();
    if (!allTestsArePassed)
    {
        return TEST_FAILED;
    }
    if (argc == 2 && stringsAreEqual(argv[1], "-test"))
    {
        return SUCCESS;
    }
    return console() ? BAD_ALLOCATION : SUCCESS;
}
