#include "test.h"

#define TEST_FAILED -1
#define SUCCESS 0

int main(void)
{
    return test() ? SUCCESS : TEST_FAILED;
}
