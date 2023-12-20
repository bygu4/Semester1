#include "console.h"
#include "test.h"
#include "str.h"

int main(const unsigned int argc, const char* const argv[])
{
    if (!test())
    {
        return TEST_FAILED;
    }
    if (argc == 2 && stringsAreEqual(argv[1], "-test"))
    {
        return SUCCESS;
    }
    return console();
}
