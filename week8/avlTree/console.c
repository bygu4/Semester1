#include "console.h"
#include "avlTree.h"
#include "str.h"
#include <stdlib.h>

enum command {
    quitCommand = 0,
    addCommand = 1,
    getCommand = 2,
    findCommand = 3,
    deleteCommand = 4
};

static bool addNodeConsole(AvlTree* const tree)
{
    printf("Enter the key: ");
    char* key = getString('\n');
    printf("\nEnter data: ");
    char* data = getString('\n');
    if (key == NULL || data == NULL)
    {
        free(key);
        free(data);
        return true;
    }
    bool errorOccured = addNode(tree, key, data);
    free(key);
    free(data);
    if (errorOccured)
    {
        return true;
    }
    printf("Item added\n");
    return false;
}

static bool getDataConsole(AvlTree* const tree)
{
    printf("Enter the key: ");
    char* key = getString('\n');
    if (key == NULL)
    {
        return true;
    }
    char* output = getData(tree, key);
    if (output == NULL)
    {
        printf("Key not found\n");
    }
    else
    {
        printf("%s\n", output);
    }
    free(key);
    return false;
}

static bool findKeyConsole(AvlTree* const tree)
{
    printf("Enter the key: ");
    char* key = getString('\n');
    if (key == NULL)
    {
        return true;
    }
    bool keyFound = findKey(tree, key);
    if (keyFound)
    {
        printf("Key is in dictionary\n");
    }
    else
    {
        printf("Key is not in dictionary\n");
    }
    free(key);
    return false;
}

static bool deleteNodeConsole(AvlTree* const tree)
{
    printf("Enter the key: ");
    char* key = getString('\n');
    if (key == NULL)
    {
        return true;
    }
    bool deleted = deleteNode(tree, key);
    if (deleted)
    {
        printf("Item deleted\n");
    }
    else
    {
        printf("Key not found\n");
    }
    free(key);
    return false;
}

int console(void)
{
    AvlTree* tree = createTree();
    if (tree == NULL)
    {
        printf("An error occured\n");
        return BAD_ALLOCATION;
    }

    printf("Command list:\n0: exit\n");
    printf("1: add an item to the dictionary\n2: get an item by the key\n");
    printf("3: check if the key is in the dictionary\n4: delete an item by the key\n\n");

    bool errorOccured = false;
    int command = -1;
    while (command != quitCommand)
    {
        printf("Enter a command: ");
        scanf_s("%d", &command);
        getchar();
        switch (command)
        {
        case quitCommand:
            continue;
        case addCommand:
            errorOccured = addNodeConsole(tree);
            break;
        case getCommand:
            errorOccured = getDataConsole(tree);
            break;
        case findCommand:
            errorOccured = findKeyConsole(tree);
            break;
        case deleteCommand:
            errorOccured = deleteNodeConsole(tree);
            break;
        default:
            printf("Unknown command\n");
            break;
        }
        printf("\n");
        if (errorOccured)
        {
            freeTree(&tree);
            printf("An error occured\n");
            return BAD_ALLOCATION;
        }
    }
    freeTree(&tree);
    return SUCCESS;
}
