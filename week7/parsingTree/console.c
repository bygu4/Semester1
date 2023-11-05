#include "console.h"
#include "parsingTree.h"

int console(void)
{
    ParsingTree* tree = NULL;
    int errorCode = buildTree(&tree, NAME_OF_FILE);
    if (errorCode != SUCCESS)
    {
        if (errorCode == FILE_NOT_FOUND)
        {
            printf("File not found\n");
        }
        return errorCode;
    }
    const int result = calculateTree(tree, true, &errorCode);
    freeTree(&tree);
    printf("\n");
    if (errorCode != SUCCESS)
    {
        return errorCode;
    }
    printf("Result: %d\n", result);
    return SUCCESS;
}
