#include "test.h"

int main(void)
{
    if (!test())
    {
        return TEST_FAILED;
    }
    return SUCCESS;
}