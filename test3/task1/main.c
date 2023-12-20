#include "logic.h"
#include "test.h"

#define TEST_FAILED -1
#define SUCCESS 0

int main(void)
{
    if (!test())
    {
        return TEST_FAILED;
    }
    return SUCCESS;
}
