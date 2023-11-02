#include "console.h"
#include "test.h"

int main(void)
{
    const bool allTestsArePassed = test();
    if (!allTestsArePassed)
    {
        return TEST_FAILED;
    }
    const int errorCode = console();
    if (errorCode != SUCCESS)
    {
        printf("An error occured\n");
        return errorCode;
    }
}
