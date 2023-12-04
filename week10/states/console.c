#include "console.h"
#include "distribute.h"

int console(void)
{
    Graph* graph = NULL;
    int errorCode = createGraph(&graph, NAME_OF_FILE);
    if (errorCode != SUCCESS)
    {
        printf(errorCode == FILE_NOT_FOUND ? "File not found\n" : "An error occured\n");
        return errorCode;
    }
    bool errorOccured = distribute(graph);
    if (errorOccured)
    {
        return BAD_ALLOCATION;
    }
    printStates(graph);
    freeGraph(&graph);
    return SUCCESS;
}
