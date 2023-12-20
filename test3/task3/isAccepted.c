#include "isAccepted.h"
#include <ctype.h>

enum State {
    startState = 0,
    letterState = 1,
    sequenceState = 2,
};

static bool startPassed(const char current, unsigned int* const state)
{
    if (isalpha(current))
    {
        *state = letterState;
        return true;
    }
    return false;
}

static bool letterPassed(const char current, unsigned int* const state)
{
    if (isalpha(current) || isdigit(current) || current == '_')
    {
        *state = sequenceState;
        return true;
    }
    return false;
}

static bool sequencePassed(const char current, unsigned int* const state)
{
    if (isalpha(current) || isdigit(current) || current == '_')
    {
        *state = sequenceState;
        return true;
    }
    return false;
}

static bool isFinalState(const unsigned int state)
{
    return state == letterState || state == sequenceState;
}

bool isAccepted(const char* const sequence)
{
    unsigned int state = startState;
    size_t index = 0;
    char current = sequence[index];
    while (current != '\0')
    {
        bool (*statePassed)(const char, unsigned int*) = startPassed;
        switch (state)
        {
        case startState:
            statePassed = startPassed;
            break;
        case letterState:
            statePassed = letterPassed;
            break;
        case sequenceState:
            statePassed = sequencePassed;
            break;
        }
        if (!statePassed)
        {
            return false;
        }
        ++index;
        current = sequence[index];
    }
    return isFinalState(state);
}
