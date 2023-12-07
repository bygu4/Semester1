#include "console.h"
#include "test.h"
#include <stdio.h>

int main(const unsigned int argc, const char argv[])
{
    const bool allTestsArePassed = test();
    if (!allTestsArePassed)
    {
        return TEST_FAILED;
    }
    if (argc == 2 && argv[1] == 't')
    {
        return SUCCESS;
    }
    return console() ? BAD_ALLOCATION : SUCCESS;
}
