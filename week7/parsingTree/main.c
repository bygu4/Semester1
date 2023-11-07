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
    return errorCode;
}
