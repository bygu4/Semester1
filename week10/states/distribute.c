#include "distribute.h"

bool distribute(Graph* const graph)
{
    if (numberOfCapitals(graph) == 0)
    {
        return false;
    }
    size_t remaining = numberOfCities(graph) - numberOfCapitals(graph);
    unsigned int state = 1;
    while (remaining > 0)
    {
        bool occupied = false;
        bool errorOccured = occupy(graph, state, &occupied);
        if (errorOccured)
        {
            return true;
        }
        if (occupied)
        {
            --remaining;
        }
        ++state;
        if (state > numberOfCapitals(graph))
        {
            state = 1;
        }
    }
    return false;
}
