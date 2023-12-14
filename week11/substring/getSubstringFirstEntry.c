#include "getSubstringFirstEntry.h"

// Кнут-Моррис-Пратт
size_t getSubstringFirstEntry(const char* const substring, const char* const string, bool* const found)
{
    size_t prefixLength = 0;
    for (size_t i = 0; ; ++i)
    {
        if (substring[prefixLength] == '\0')
        {
            *found = true;
            return i - prefixLength;
        }
        if (string[i] == '\0')
        {
            *found = false;
            return 0;
        }
        if (string[i] == substring[prefixLength])
        {
            ++prefixLength;
        }
        else
        {
            prefixLength = 0;
        }
    }
    *found = false;
    return 0;
}
