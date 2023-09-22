#include <stdio.h>
#include <math.h>

int main()
{
    int possibleSums[28] = { 0 };
    for (int n1 = 0; n1 < 10; ++n1)
    {
        for (int n2 = 0; n2 < 10; ++n2)
        {
            for (int n3 = 0; n3 < 10; ++n3)
            {
                possibleSums[n1 + n2 + n3] += 1;
            }
        }
    }
    int numberOfTickets = 0;
    for (int i = 0; i < 28; ++i)
    {
        numberOfTickets += pow(possibleSums[i], 2);
    }
    printf("Number of fortunate tickets: %d", numberOfTickets);
}