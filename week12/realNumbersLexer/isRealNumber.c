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
    if (isdigit(current))
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
    if (current == '.')
    {
        *state = decimalSign;
        return true;
    }
    if (current == 'E')
    {
        *state = exponent;
        return true;
    }
    if (isspace(current))
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
    if (current == 'E')
    {
        *state = exponent;
        return true;
    }
    if (isspace(current))
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
    if (isdigit(current))
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
    if (isspace(current))
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
        bool (*method)(const char, unsigned int* const) = startMethod;
        switch (state)
        {
        case start:
            method = startMethod;
            break;
        case integer:
            method = integerMethod;
            break;
        case decimalSign:
            method = decimalSignMethod;
            break;
        case decimalDigit:
            method = decimalDigitMethod;
            break;
        case exponent:
            method = exponentMethod;
            break;
        case exponentialSign:
            method = exponentialSignMethod;
            break;
        case exponentialDigit:
            method = exponentialDigitMethod;
            break;
        case end:
            method = endMethod;
            break;
        }
        if (!method(current, &state))
        {
            return false;
        }
        ++index;
        current = sequence[index];
    }
    return isFinalState(state);
}
