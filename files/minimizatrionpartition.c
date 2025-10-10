#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define MAX_STATES 50
#define MAX_SYMBOLS 10
int nStates, nSymbols, startState, nFinals;
int finalStates[MAX_STATES];
int transition[MAX_STATES][MAX_SYMBOLS];
// Check if a state is final
bool isFinal(int state)
{
    for (int i = 0; i < nFinals; i++)
    {
        if (finalStates[i] == state)
            return true;
    }
    return false;
}
// DFA minimization using partition refinement
void minimizeDFA()
{
    int partition[MAX_STATES], newPartition[MAX_STATES];
    int i, j, k, changed;
    // Initial partition: final states (1) and non-final (0)
    for (i = 0; i < nStates; i++)
    {
        partition[i] = isFinal(i) ? 1 : 0;
    }
    do
    {
        changed = 0;
        int group = 0;
        for (i = 0; i < nStates; i++)
        {
            newPartition[i] = -1;
            for (j = 0; j < i; j++)
            {
                if (partition[i] == partition[j])
                {
                    int same = 1;
                    for (k = 0; k < nSymbols; k++)
                    {
                        if (partition[transition[i][k]] != partition[transition[j][k]])
                        {
                            same = 0;
                            break;
                        }
                    }
                    if (same)
                    {
                        newPartition[i] = newPartition[j];
                        break;
                    }
                }
            }
            if (newPartition[i] == -1)
            {
                newPartition[i] = group++;
            }
        }
        for (i = 0; i < nStates; i++)
        {
            if (partition[i] != newPartition[i])
            {
                changed = 1;
            }
            partition[i] = newPartition[i];
        }
    } while (changed);
    // Print minimized groups
    printf("\nMinimized DFA States (equivalence classes):\n");
    for (i = 0; i < nStates; i++)
    {
        printf("State %d -> Group %d\n", i, partition[i]);
    }
}
int main()
{
    int i, j;
    printf("Enter number of states: ");
    scanf("%d", &nStates);
    printf("Enter number of input symbols: ");
    scanf("%d", &nSymbols);
    printf("Enter transition table (rows: states, cols: symbols):\n");
    for (i = 0; i < nStates; i++)
    {
        for (j = 0; j < nSymbols; j++)
        {
            scanf("%d", &transition[i][j]);
        }
    }
    printf("Enter start state: ");
    scanf("%d", &startState);
    printf("Enter number of final states: ");
    scanf("%d", &nFinals);
    printf("Enter final states: ");
    for (i = 0; i < nFinals; i++)
    {
        scanf("%d", &finalStates[i]);
    }
    minimizeDFA();
    return 0;
}
