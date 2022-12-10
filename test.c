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

/*printf("\n\tbefore test for the connected\n");
for(i=0; i<node; i++)
{
    printf("\tnodeLabel[%d]: %d\n", i, nodeLabel[i]);
}*/

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


/*printf("\n\tafter test for the connected\n");
for(i=0; i<node; i++)
{
    printf("\tnodeLabel[%d]: %d\n", i, nodeLabel[i]);
}*/

        if(label < node) //graph is disconnected
        {
            //result[index] = 2147483647;
            //index++;
            printf("no\n");
            continue;
        }

        //put node into different set
        for(i=0; i<node; i++)
        {
            nodeLabel[i] = i;
        }

/*printf("\n\tafter put node into different set\n");
for(i=0; i<node; i++)
{
    printf("\tnodeLabel[%d]: %d\n", i, nodeLabel[i]);
}
printf("\n");*/

        //MaxSpanningTree by kruskal
        mergeSortMax(0, edge-1);

        planOne = 0;
        for(i=0; i<edge; i++)
        {
//printf("\t%d %d %d\n", nodeOne[i], nodeTwo[i], nodeCost[i]);

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

//printf("\t\tnodeOne %d and nodeTwo %d is not in the different set, planOne=%d\n", one, two, planOne);
            }else
            {
//printf("\t\tnodeOne %d and nodeTwo %d is in the same set, planOne=%d\n", one, two, planOne);
            }
        }

      for(i=1; i<node; i++)
      {
        if(nodeLabel[i-1] != nodeLabel[i])
        {
          return -1;
        }
      }
      
/*printf("\n\tplanOne: %d\n", planOne);

printf("\n\tin the beginning of plan two\n");
for(i=0; i<node; i++)
{
    printf("\tnodeLabel[%d]: %d\n", i, nodeLabel[i]);
}*/

        //for plan two
        mergeSortMin(0, edge-1);

        //reset nodeLabel (1)
        for(i=0; i<node; i++)
        {
            nodeLabel[i] = 1;
        }

/*printf("\n\tafter reset node label (1)\n");
for(i=0; i<node; i++)
{
    printf("\tnodeLabel[%d]: %d\n", i, nodeLabel[i]);
}*/

        //label rumor (2) and its neighbor (3)
        for(i=0; i<rumor; i++)
        {
            temp = nodeRumor[i];

            nodeLabel[temp] = 2;

            for(j=0; j<node; j++)
            {
                if(graph[temp][j] > -1)
                {
                    if(nodeLabel[j] == 1)
                    {
                        nodeLabel[j] = 3;
                    }
                }
            }
        }

/*printf("\n\tafter label with rumor (2) and its neighbor (3)\n");
for(i=0; i<node; i++)
{
    printf("\tnodeLabel[%d]: %d\n", i, nodeLabel[i]);
}
printf("\n\tcounting the cost of rumor\n");*/

        //count cost by rumor
        planTwo = 0;
        for(i=0; i<edge; i++)
        {
//printf("\t%d %d %d\n", nodeOne[i], nodeTwo[i], nodeCost[i]);

            one = nodeOne[i];
            two = nodeTwo[i];

            if((nodeLabel[one]==2) || (nodeLabel[two]==2))
            {
                planTwo = planTwo + nodeCost[i];
//printf("\t\tnodeOne %d or nodeTwo %d is rumor, planTwo=%d\n", one, two, planTwo);
            }
        }

        //reset label of rumor to 3
        for(i=0; i<node; i++)
        {
            if(nodeLabel[i] == 2)
            {
                nodeLabel[i] = 3;
            }
        }

        //put different group of "3" into different set
        label = 4;
        while(1)
        {
            for(i=0; i<node; i++) //find "3"
            {
                if(nodeLabel[i] == 3)
                {
                    now = i;
                    break;
                }
            }
            if(i == node) //no more "3"
            {
                break;
            }

            nodeLabel[now] = label;
            start = 0;
            end = 0;
            while(1)
            {
                for(j=0; j<node; j++)
                {
                    if(graph[now][j] > -1)
                    {
                        if(nodeLabel[j] == 3)
                        {
                            nodeLabel[j] = label;
                            nodeNext[end] = j;
                            end++;
                        }
                    }
                }

                if(start == end)
                {
                    label++;
                    break;
                }

                now = nodeNext[start];
                start++;
            }
        }

        //put each "1" into different set
        for(i=0; i<node; i++)
        {
            if(nodeLabel[i] == 1)
            {
                nodeLabel[i] = label;
                label++;
            }
        }


/*printf("\n\tput in different set\n");
for(i=0; i<node; i++)
{
    printf("\tnodeLabel[%d]: %d\n", i, nodeLabel[i]);
}
printf("\n\tcount for MST\n");*/

        //MST by kruskal
        for(i=0; i<edge; i++)
        {
//printf("\t%d %d %d\n", nodeOne[i], nodeTwo[i], nodeCost[i]);

            one = nodeOne[i];
            two = nodeTwo[i];

            if(nodeLabel[one] != nodeLabel[two])
            {
                planTwo = planTwo + nodeCost[i];
                //temp = nodeLabel[one];

                for(j=0; j<node; j++)
                {
                    if(nodeLabel[two]==nodeLabel[j] && j!=two)
                    {
                        nodeLabel[j] = nodeLabel[one];
                    }
                }

                nodeLabel[two] = nodeLabel[one];

//printf("\t\tnodeOne %d and nodeTwo %d is not in the different set, planTwo=%d\n", one, two, planTwo);
            }else
            {
//printf("\t\tnodeOne %d and nodeTwo %d is in the same set, planTwo=%d\n", one, two, planTwo);
            }
        }

/*printf("\n\tplanTwo: %d\n", planTwo);

printf("\n");
for(i=0; i<node; i++)
{
    printf("\tnodeLabel[%d]: %d\n", i, nodeLabel[i]);
}

printf("\n\tans: %d\n", planOne-planTwo);*/

      for(i=1; i<node; i++)
      {
        if(nodeLabel[i-1] != nodeLabel[i])
        {
          return -1;
        }
      }
      
        printf("%d\n", planOne-planTwo);
        //result[index] = planOne-planTwo;
        //index++;
    }

    /*for(i=0; i<index; i++)
    {
        if(result[i] == 2147483647)
        {
            printf("no\n");
        }else
        {
            printf("%d\n", result[i]);
        }
    }*/

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

