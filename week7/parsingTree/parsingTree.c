#include "parsingTree.h"
#include "getInt.h"
#include <stdlib.h>

enum operations {
    addition = '+',
    substraction = '-',
    multiplication = '*',
    division = '/'
};

static bool isOperation(const char character)
{
    return character == addition || character == substraction ||
        character == multiplication || character == division;
}

typedef struct {
    int value;
    struct Node* leftChild;
    struct Node* rightChild;
} Node;

struct ParsingTree {
    Node* root;
};

static void freeTreeRecursion(Node* node)
{
    if (node == NULL)
    {
        return;
    }
    if (node->leftChild != NULL)
    {
        freeTreeRecursion(node->leftChild);
    }
    if (node->rightChild != NULL)
    {
        freeTreeRecursion(node->rightChild);
    }
    free(node);
}

void freeTree(ParsingTree** const tree)
{
    freeTreeRecursion((*tree)->root);
    free(*tree);
    *tree = NULL;
}

static Node* makeNode(const int value)
{
    Node* node = (Node*)malloc(sizeof(Node));
    if (node == NULL)
    {
        return NULL;
    }
    node->value = value;
    node->leftChild = NULL;
    node->rightChild = NULL;
    return node;
}

static ParsingTree* buildTreeRecursion(FILE* const stream)
{
    ParsingTree* tree = (ParsingTree*)calloc(1, sizeof(ParsingTree));
    if (tree == NULL)
    {
        return NULL;
    }
    char character = fgetc(stream);
    while (character != ')' && !feof(stream))
    {
        if (character == '(')
        {
            ParsingTree* childTree = buildTreeRecursion(stream);
            if (childTree == NULL)
            {
                freeTree(&tree);
                return NULL;
            }
            Node* childTreeRoot = childTree->root;
            free(childTree);
            if (tree->root == NULL)
            {
                tree->root = childTreeRoot;
            }
            else if (tree->root->leftChild == NULL)
            {
                tree->root->leftChild = childTreeRoot;
            }
            else
            {
                tree->root->rightChild = childTreeRoot;
            }
        }
        else if (isOperation(character))
        {
            tree->root = makeNode((int)character);
            if (tree->root == NULL)
            {
                free(tree);
                return NULL;
            }
        }
        else if (isdigit(character))
        {
            ungetc(character, stream);
            bool errorOccured = false;
            const int value = getInt(stream, &errorOccured);
            if (errorOccured)
            {
                freeTree(&tree);
                return NULL;;
            }
            Node* node = makeNode(value);
            if (node == NULL)
            {
                freeTree(&tree);
                return NULL;
            }
            if (tree->root == NULL)
            {
                tree->root = node;
            }
            else if (tree->root->leftChild == NULL)
            {
                tree->root->leftChild = node;
            }
            else
            {
                tree->root->rightChild = node;
            }
        }
        character = fgetc(stream);
    }
    return tree;
}

int buildTree(ParsingTree** const tree, const char* const nameOfFile)
{
    FILE* inputFile = NULL;
    int errorCode = fopen_s(&inputFile, nameOfFile, "r");
    if (errorCode != SUCCESS)
    {
        return errorCode;
    }
    *tree = buildTreeRecursion(inputFile);
    fclose(inputFile);
    if (*tree == NULL)
    {
        return BAD_ALLOCATION;
    }
    return SUCCESS;
}

static int calculate(const int number1, const int number2, const char operation)
{
    int result = 0;
    switch (operation)
    {
    case addition:
        result = number1 + number2;
        break;
    case substraction:
        result = number1 - number2;
        break;
    case multiplication:
        result = number1 * number2;
        break;
    case division:
        result = number1 / number2;
        break;
    }
    return result;
}

static int calculateTreeRecursion(const Node* const node, const bool printTree, int* const errorCode)
{
    if (node == NULL)
    {
        return 0;
    }
    if (node->leftChild == NULL && node->rightChild == NULL)
    {
        printf(printTree ? "%d" : "", node->value);
        return node->value;
    }
    printf(printTree ? "(" : "");
    const int number1 = calculateTreeRecursion(node->leftChild, printTree, errorCode);
    if (*errorCode != SUCCESS)
    {
        return 0;
    }
    printf(printTree ? " %c " : "", (char)node->value);
    const int number2 = calculateTreeRecursion(node->rightChild, printTree, errorCode);
    if (*errorCode != SUCCESS)
    {
        return 0;
    }
    printf(printTree ? ")" : "");
    if ((char)node->value == division && number2 == 0)
    {
        *errorCode = DIVISION_BY_ZERO;
        return 0;
    }
    *errorCode = SUCCESS;
    return calculate(number1, number2, (char)node->value);
}

int calculateTree(const ParsingTree* const tree, const bool printTree, int* const errorCode)
{
    return calculateTreeRecursion(tree->root, printTree, errorCode);
}
