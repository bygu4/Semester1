#include "deleteOddElements.h"

void deleteOddElements(List* const list)
{
    setCurrent(list);
    while (!currentIsNull(list))
    {
        deleteElement(list);
        switchCurrent(list);
    }
}
