#include "isRealNumber.h"
#include <ctype.h>

enum states {
    start = 0,
    integer = 1,
    decimalSign = 2,
    decimalDigit = 3,
    exponent = 4,
    exponentialSign = 5,
    exponentialDigit = 6,
    end = 7
};

static bool startMethod(const char current, unsigned int* const state)
{
    if (isspace(current))
    {
        *state = start;
        return true;
    }
    else if (isdigit(current))
    {
        *state = integer;
        return true;
    }
    return false;
}

static bool integerMethod(const char current, unsigned int* const state)
{
    if (isdigit(current))
    {
        *state = integer;
        return true;
    }
    else if (current == '.')
    {
        *state = decimalSign;
        return true;
    }
    else if (current == 'E')
    {
        *state = exponent;
        return true;
    }
    else if (isspace(current))
    {
        *state = end;
        return true;
    }
    return false;
}

static bool decimalSignMethod(const char current, unsigned int* const state)
{
    if (isdigit(current))
    {
        *state = decimalDigit;
        return true;
    }
    return false;
}

static bool decimalDigitMethod(const char current, unsigned int* const state)
{
    if (isdigit(current))
    {
        *state = decimalDigit;
        return true;
    }
    else if (current == 'E')
    {
        *state = exponent;
        return true;
    }
    else if (isspace(current))
    {
        *state = end;
        return true;
    }
    return false;
}

static bool exponentMethod(const char current, unsigned int* const state)
{
    if (current == '+' || current == '-')
    {
        *state = exponentialSign;
        return true;
    }
    else if (isdigit(current))
    {
        *state = exponentialDigit;
        return true;
    }
    return false;
}

static bool exponentialSignMethod(const char current, unsigned int* const state)
{
    if (isdigit(current))
    {
        *state = decimalDigit;
        return true;
    }
    return false;
}

static bool exponentialDigitMethod(const char current, unsigned int* const state)
{
    if (isdigit(current))
    {
        *state = exponentialDigit;
        return true;
    }
    else if (isspace(current))
    {
        *state = end;
        return true;
    }
    return false;
}

static bool endMethod(const char current, unsigned int* const state)
{
    if (isspace(current))
    {
        *state = end;
        return true;
    }
    return false;
}

static bool isFinalState(const unsigned int state)
{
    return state == integer || state == decimalDigit || 
        state == exponentialDigit || state == end;
}

bool isRealNumber(const char* const sequence)
{
    unsigned int state = start;
    size_t index = 0;
    char current = sequence[index];
    while (current != '\0')
    {
        switch (state)
        {
        case start:
            if (!startMethod(current, &state))
            {
                return false;
            }
            break;
        case integer:
            if (!integerMethod(current, &state))
            {
                return false;
            }
            break;
        case decimalSign:
            if (!decimalSignMethod(current, &state))
            {
                return false;
            }
            break;
        case decimalDigit:
            if (!decimalDigitMethod(current, &state))
            {
                return false;
            }
            break;
        case exponent:
            if (!exponentMethod(current, &state))
            {
                return false;
            }
            break;
        case exponentialSign:
            if (!exponentialSignMethod(current, &state))
            {
                return false;
            }
            break;
        case exponentialDigit:
            if (!exponentialDigitMethod(current, &state))
            {
                return false;
            }
            break;
        case end:
            if (!endMethod(current, &state))
            {
                return false;
            }
            break;
        }
        ++index;
        current = sequence[index];
    }
    return isFinalState(state);
}
