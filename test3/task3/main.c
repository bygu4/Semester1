#include "test.h"
#include "console.h"
#include "str.h"

#define TEST_FAILED -1
#define SUCCESS 0

int main(const int argc, const char* const argv[])
{
    if (!testIsPassed())
    {
        return TEST_FAILED;
    }
    if (argc == 2 && stringsAreEqual(argv[1], "-test"))
    {
        return SUCCESS;
    }
    return console();
}
