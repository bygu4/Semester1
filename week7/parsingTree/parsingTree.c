#include "parsingTree.h"
#include <stdlib.h>
#include <ctype.h>

enum operations {
    additionOp = '+',
    substractionOp = '-',
    multiplicationOp = '*',
    divisionOp = '/'
};

static bool isOperation(const char character)
{
    return character == additionOp || character == substractionOp ||
        character == multiplicationOp || character == divisionOp;
}

typedef struct {
    int value;
    struct Node* leftChild;
    struct Node* rightChild;
} Node;

struct ParsingTree {
    Node* root;
};

static void freeNodeWithDescendants(Node* node)
{
    if (node == NULL)
    {
        return;
    }
    freeNodeWithDescendants(node->leftChild);
    freeNodeWithDescendants(node->rightChild);
    free(node);
}

void freeTree(ParsingTree** const tree)
{
    freeNodeWithDescendants((*tree)->root);
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

static int getInt(FILE* const stream)
{
    int result = 0;
    char character = fgetc(stream);
    while (isdigit(character))
    {
        result = result * 10 + (int)(character - '0');
        character = fgetc(stream);
    }
    ungetc(character, stream);
    return result;
}

static Node* buildTreeRecursion(FILE* const stream, int* const errorCode)
{
    Node* node = NULL;
    char character = fgetc(stream);
    while (character != ')' && !feof(stream))
    {
        if (isdigit(character))
        {
            ungetc(character, stream);
            int number = getInt(stream);
            node = makeNode(number);
            if (node == NULL)
            {
                *errorCode = BAD_ALLOCATION;
                return NULL;
            }
            break;
        }
        else if (isOperation(character))
        {
            node = makeNode((int)character);
            if (node == NULL)
            {
                *errorCode = BAD_ALLOCATION;
                return NULL;
            }
            node->leftChild = buildTreeRecursion(stream, errorCode);
            node->rightChild = buildTreeRecursion(stream, errorCode);
            if (node->leftChild == NULL || node->rightChild == NULL)
            {
                freeNodeWithDescendants(node);
                *errorCode = BAD_ALLOCATION;
                return NULL;
            }
        }
        character = fgetc(stream);
    }
    *errorCode = SUCCESS;
    return node;
}

int buildTree(ParsingTree** const tree, const char* const nameOfFile)
{
    FILE* inputFile = NULL;
    int errorCode = fopen_s(&inputFile, nameOfFile, "r");
    if (errorCode != SUCCESS)
    {
        return errorCode;
    }
    *tree = (ParsingTree*)malloc(sizeof(ParsingTree));
    if (*tree == NULL)
    {
        fclose(inputFile);
        return BAD_ALLOCATION;
    }
    (*tree)->root = buildTreeRecursion(inputFile, &errorCode);
    fclose(inputFile);
    if (errorCode != SUCCESS)
    {
        freeTree(tree);
    }
    return errorCode;
}

static int calculate(const int number1, const int number2, const char operation)
{
    int result = 0;
    switch (operation)
    {
    case additionOp:
        result = number1 + number2;
        break;
    case substractionOp:
        result = number1 - number2;
        break;
    case multiplicationOp:
        result = number1 * number2;
        break;
    case divisionOp:
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
    if ((char)node->value == divisionOp && number2 == 0)
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
