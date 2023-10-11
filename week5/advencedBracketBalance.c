#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define SIZE_OF_BUFFER 128

typedef struct {
    char expectedBracket;
    struct Stack* next;
} Stack;

int push(Stack** head, const char bracket)
{
    Stack* next = malloc(sizeof(Stack));
    if (next == NULL)
    {
        return 1;
    }
    next->expectedBracket = bracket;
    next->next = *head;
    *head = next;
    return 0;
}

void pop(Stack** head)
{
    Stack* next = (*head)->next;
    free(*head);
    *head = next;
}

void freeStack(Stack** head)
{
    while (*head != NULL)
    {
        pop(head);
    }
}

char getClosingBracket(const char bracket)
{
    if (bracket == '(')
    {
        return ')';
    }
    if (bracket == '[')
    {
        return ']';
    }
    if (bracket == '{')
    {
        return '}';
    }
    return NULL;
}

bool checkBracketBalance(const char* string, int* errorCode)
{
    Stack* head = NULL;
    size_t lengthOfString = strlen(string);
    for (int i = 0; i < lengthOfString; ++i)
    {
        char character = string[i];
        if (character == '(' || character == '[' || character == '{')
        {
            char closingBracket = getClosingBracket(character);
            int pushErrorCode = push(&head, closingBracket);
            if (pushErrorCode != 0)
            {
                *errorCode = 1;
                freeStack(&head);
                return false;
            }
        }
        else if (head != NULL && character == head->expectedBracket)
        {
            pop(&head);
        }
        else if ((character == ')' || character == ']' || character == '}')
            && (head == NULL || character != head->expectedBracket))
        {
            freeStack(&head);
            return false;
        }
    }
    if (head == NULL)
    {
        return true;
    }
    freeStack(&head);
    return false;
}

bool allTestArePassed()
{
    int errorCode = 0;
    bool testOneIsPassed = checkBracketBalance("[({}[])]", &errorCode);
    bool testTwoIsPassed = !checkBracketBalance("{}{", &errorCode);
    bool testThreeIsPassed = !checkBracketBalance(")", &errorCode);
    bool testFourIsPassed = !checkBracketBalance("([)]", &errorCode);
    bool testFiveIsPassed = checkBracketBalance("(a + b)^2 = (a^2 + 2ab + b^2)", &errorCode);
    bool testSixIsPassed = checkBracketBalance("", &errorCode);
    return errorCode == 0 && testOneIsPassed && testTwoIsPassed && testThreeIsPassed
        && testFourIsPassed && testFiveIsPassed && testSixIsPassed;
}

int main()
{
    if (!allTestArePassed())
    {
        printf("An error occured");
        return -1;
    }
    char inputString[SIZE_OF_BUFFER] = { '\0' };
    printf("Input a bracket sequence: ");
    scanf_s("%s", inputString, SIZE_OF_BUFFER - 1);

    int errorCode = 0;
    bool sequenceIsCorrect = checkBracketBalance(inputString, &errorCode);
    if (errorCode != 0)
    {
        printf("An error occured");
        return -1;
    }
    printf(sequenceIsCorrect ? "Correct" : "Incorrect");
}