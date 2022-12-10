#include <stdlib.h>
#include <stdio.h>

void mergeSortMax(int head, int tail);
void mergeMax(int head, int mid, int tail);

void mergeSortMin(int head, int tail);
void mergeMin(int head, int mid, int tail);

int nodeOne[124750];
int nodeTwo[124750];
int nodeCost[124750];
int nodeLabel[500];
int nodeNext[500];
int nodeRumor[500];
int nodeRumorLabel[500];
int graph[500][500];
int result[500];

int main()
{
    int i, j, k, temp, tmp;
    int one, two, cost;
    int node, edge, rumor;
    int start, end, label, now;
    int planOne, planTwo;
    int index = 0;

    while(scanf("%d", &node) != EOF)
    {
        scanf("%d", &edge);
        scanf("%d", &rumor);

        //reset array
        for(i=0; i<node; i++)
        {
            for(j=0; j<node; j++)
            {
                graph[i][j] = -1;
            }
            nodeLabel[i] = 0;
            nodeNext[i] = 0;
        }

        for(i=0; i<edge; i++)
        {
            scanf("%d", &one);
            scanf("%d", &two);
            scanf("%d", &cost);

            graph[one][two] = cost;
            graph[two][one] = cost;

            nodeOne[i] = one;
            nodeTwo[i] = two;
            nodeCost[i] = cost;
        }

        for(i=0; i<rumor; i++)
        {
            scanf("%d", &temp);

            nodeRumor[i] = temp;
        }

        //test for the connected component
        now = 0;
        label = 1;
        nodeLabel[now] = 1;
        start = 0;
        end = 0;
        while(1)
        {
            for(j=0; j<node; j++)
            {
                if(graph[now][j] > -1)
                {
                    if(nodeLabel[j] == 0)
                    {
                        nodeLabel[j] = 1;
                        nodeNext[end] = j;
                        end++;
                        label++;
                    }
                }
            }

            if(start == end)
            {
                break;
            }

            now = nodeNext[start];
            start++;
        }

        if(label < node) //graph is disconnected
        {
            result[index] = 2147483647;
            index++;
            //printf("no\n");
            continue;
        }

        //put node into different set
        for(i=0; i<node; i++)
        {
            nodeLabel[i] = i;
        }

        //MaxSpanningTree by kruskal
        mergeSortMax(0, edge-1);

        planOne = 0;
        for(i=0; i<edge; i++)
        {
            one = nodeOne[i];
            two = nodeTwo[i];

            if(nodeLabel[one] != nodeLabel[two])
            {
                planOne = planOne + nodeCost[i];
                temp = nodeLabel[one];

                for(j=0; j<node; j++)
                {
                    if(nodeLabel[two]==nodeLabel[j] && j!=two)
                    {
                        nodeLabel[j] = temp;
                    }
                }
                nodeLabel[two] = temp;
            }
        }

        //for plan two
        mergeSortMin(0, edge-1);

        //reset nodeLabel
        for(i=0; i<node; i++)
        {
            nodeLabel[i] = i;
        }

        //label rumor
        for(i=0; i<node; i++)
        {
            nodeRumorLabel[i] = 0;
        }
        for(i=0; i<rumor; i++)
        {
            temp = nodeRumor[i];

            nodeRumorLabel[temp] = 1;
        }

        //count cost by rumor
        planTwo = 0;
        for(i=0; i<edge; i++)
        {
            one = nodeOne[i];
            two = nodeTwo[i];

            if((nodeRumorLabel[one]==1) || (nodeRumorLabel[two]==1))
            {
                planTwo = planTwo + nodeCost[i];

                temp = nodeLabel[one];

                for(j=0; j<node; j++)
                {
                    if(nodeLabel[two]==nodeLabel[j] && j!=two)
                    {
                        nodeLabel[j] = temp;
                    }
                }
                nodeLabel[two] = temp;
            }
        }

        //MST by kruskal
        for(i=0; i<edge; i++)
        {
            one = nodeOne[i];
            two = nodeTwo[i];

            if(nodeLabel[one] != nodeLabel[two])
            {
                planTwo = planTwo + nodeCost[i];
                temp = nodeLabel[one];

                for(j=0; j<node; j++)
                {
                    if(nodeLabel[two]==nodeLabel[j] && j!=two)
                    {
                        nodeLabel[j] = temp;
                    }
                }
                nodeLabel[two] = temp;
            }
        }

        //printf("%d\n", planOne-planTwo);
        result[index] = planOne-planTwo;
        index++;
    }

    for(i=0; i<index; i++)
    {
        if(result[i] == 2147483647)
        {
            printf("no\n");
        }else
        {
            printf("%d\n", result[i]);
        }
    }

    return 0;
}


void mergeMax(int head, int mid, int tail)
{
    int lenA = mid - head + 1;
    int lenB = tail - (mid+1) + 1;
    int *leftSubOne = (int*)malloc(sizeof(int)*(lenA+1));
    int *leftSubTwo = (int*)malloc(sizeof(int)*(lenA+1));
    int *leftSubCost = (int*)malloc(sizeof(int)*(lenA+1));
    int *rightSubOne = (int*)malloc(sizeof(int)*(lenB+1));
    int *rightSubTwo = (int*)malloc(sizeof(int)*(lenB+1));
    int *rightSubCost = (int*)malloc(sizeof(int)*(lenB+1));

    int leftIndexCost = 0;
    int rightIndexCost = 0;

    for(leftIndexCost=0; leftIndexCost<lenA; leftIndexCost++)
    {
        leftSubOne[leftIndexCost] = nodeOne[head + leftIndexCost];
        leftSubTwo[leftIndexCost] = nodeTwo[head + leftIndexCost];
        leftSubCost[leftIndexCost] = nodeCost[head + leftIndexCost];
    }

    for(rightIndexCost=0; rightIndexCost<lenB; rightIndexCost++)
    {
        rightSubOne[rightIndexCost] = nodeOne[mid + 1 + rightIndexCost];
        rightSubTwo[rightIndexCost] = nodeTwo[mid + 1 + rightIndexCost];
        rightSubCost[rightIndexCost] = nodeCost[mid + 1 + rightIndexCost];
    }

    leftSubCost[lenA] = -1;
    rightSubCost[lenB] = -1;

    leftIndexCost = 0;
    rightIndexCost = 0;

    int writePointer=0;
    for(writePointer=head; writePointer<=tail; writePointer++)
    {
        if (leftSubCost[leftIndexCost] >= rightSubCost[rightIndexCost])
        {
            nodeOne[writePointer] = leftSubOne[leftIndexCost];
            nodeTwo[writePointer] = leftSubTwo[leftIndexCost];
            nodeCost[writePointer] = leftSubCost[leftIndexCost++];
        }else
        {
            nodeOne[writePointer] = rightSubOne[rightIndexCost];
            nodeTwo[writePointer] = rightSubTwo[rightIndexCost];
            nodeCost[writePointer] = rightSubCost[rightIndexCost++];
        }
    }

    free(leftSubOne);
    free(leftSubTwo);
    free(leftSubCost);
    free(rightSubOne);
    free(rightSubTwo);
    free(rightSubCost);
}

void mergeSortMax(int head, int tail)
{
    int mid=0;
    if(head < tail)
    {
        mid = (head+tail) / 2;
        mergeSortMax(head, mid);
        mergeSortMax(mid+1, tail);
        mergeMax(head, mid, tail);
    }
}


void mergeMin(int head, int mid, int tail)
{
    int lenA = mid - head + 1;
    int lenB = tail - (mid+1) + 1;
    int *leftSubOne = (int*)malloc(sizeof(int)*(lenA+1));
    int *leftSubTwo = (int*)malloc(sizeof(int)*(lenA+1));
    int *leftSubCost = (int*)malloc(sizeof(int)*(lenA+1));
    int *rightSubOne = (int*)malloc(sizeof(int)*(lenB+1));
    int *rightSubTwo = (int*)malloc(sizeof(int)*(lenB+1));
    int *rightSubCost = (int*)malloc(sizeof(int)*(lenB+1));

    int leftIndexCost = 0;
    int rightIndexCost = 0;

    for(leftIndexCost=0; leftIndexCost<lenA; leftIndexCost++)
    {
        leftSubOne[leftIndexCost] = nodeOne[head + leftIndexCost];
        leftSubTwo[leftIndexCost] = nodeTwo[head + leftIndexCost];
        leftSubCost[leftIndexCost] = nodeCost[head + leftIndexCost];
    }

    for(rightIndexCost=0; rightIndexCost<lenB; rightIndexCost++)
    {
        rightSubOne[rightIndexCost] = nodeOne[mid + 1 + rightIndexCost];
        rightSubTwo[rightIndexCost] = nodeTwo[mid + 1 + rightIndexCost];
        rightSubCost[rightIndexCost] = nodeCost[mid + 1 + rightIndexCost];
    }

    leftSubCost[lenA] = 2147483647;
    rightSubCost[lenB] = 2147483647;

    leftIndexCost = 0;
    rightIndexCost = 0;

    int writePointer=0;
    for(writePointer=head; writePointer<=tail; writePointer++)
    {
        if (leftSubCost[leftIndexCost] <= rightSubCost[rightIndexCost])
        {
            nodeOne[writePointer] = leftSubOne[leftIndexCost];
            nodeTwo[writePointer] = leftSubTwo[leftIndexCost];
            nodeCost[writePointer] = leftSubCost[leftIndexCost++];
        }else
        {
            nodeOne[writePointer] = rightSubOne[rightIndexCost];
            nodeTwo[writePointer] = rightSubTwo[rightIndexCost];
            nodeCost[writePointer] = rightSubCost[rightIndexCost++];
        }
    }

    free(leftSubOne);
    free(leftSubTwo);
    free(leftSubCost);
    free(rightSubOne);
    free(rightSubTwo);
    free(rightSubCost);
}

void mergeSortMin(int head, int tail)
{
    int mid=0;
    if(head < tail)
    {
        mid = (head+tail) / 2;
        mergeSortMin(head, mid);
        mergeSortMin(mid+1, tail);
        mergeMin(head, mid, tail);
    }
}

