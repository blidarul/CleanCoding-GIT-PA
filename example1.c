/*Determinati daca exista sau nu drum direct intre doua restaurante dintr-o retea de tip graf*/

#include <stdlib.h>
#include <stdio.h>

typedef struct Node
{
    int value;
    struct Node *next;
} Node;

typedef struct Graph
{
    int vertexCount;
    int *visitedNodes;
    struct Node **adjacencyLists;
} Graph;

typedef struct Stack
{
    int top;
    int capacity;
    int *array;
} Stack;

Node *createNode(int value)
{
    Node *newNode = malloc(sizeof(Node));
    newNode->value = value;
    newNode->next = NULL;
    return newNode;
}

void addEdge(Graph *graph, int source, int destination)
{
    Node *newNode = createNode(destination);
    newNode->next = graph->adjacencyLists[source];
    graph->adjacencyLists[source] = newNode;
    
    newNode = createNode(source);
    newNode->next = graph->adjacencyLists[destination];
    graph->adjacencyLists[destination] = newNode;
}

Graph *createGraph(int vertexCount)
{
    Graph *graph = malloc(sizeof(Graph));
    graph->vertexCount = vertexCount;
    graph->adjacencyLists = malloc(vertexCount * sizeof(Node *));
    graph->visitedNodes = malloc(sizeof(int) * vertexCount);

    for (int i = 0; i < vertexCount; i++)
    {
        graph->adjacencyLists[i] = NULL;
        graph->visitedNodes[i] = 0;
    }    
    return graph;
}

Stack *createStack(int capacity)
{
    Stack *stack = malloc(sizeof(Stack));
    stack->array = malloc(capacity * sizeof(int));
    stack->top = -1;
    stack->capacity = capacity;
    return stack;
}

void pushToStack(int value, Stack *stack)
{
    stack->top = stack->top + 1;
    stack->array[stack->top] = value;
}

void depthFirstSearch(Graph *graph, Stack *stack, int currentVertex)
{
    Node *currentNode = graph->adjacencyLists[currentVertex];

    graph->visitedNodes[currentVertex] = 1;
    printf("%d ", currentVertex + 1);
    pushToStack(currentVertex, stack);

    while (currentNode != NULL)
    {
        int connectedVertex = currentNode->value;

        if (graph->visitedNodes[connectedVertex] == 0)
        {
            depthFirstSearch(graph, stack, connectedVertex);
        }
        currentNode = currentNode->next;
    }
}

void insertEdges(Graph *graph, int edgeCount, int vertexCount)
{
    int source, destination;
    printf("adauga %d muchii (de la 1 la %d)(scrie sursa si destinatie)\n", 
        edgeCount, vertexCount);

    for (int i = 0; i < edgeCount; i++)
    {
        scanf("%d%d", &source, &destination);
        addEdge(graph, source - 1, destination - 1);  
    }
}

void resetVisited(Graph *graph, int vertexCount)
{
    for (int i = 0; i < vertexCount; i++)
    {
        graph->visitedNodes[i] = 0;
    }
}    

void checkPath(Graph *graph, int startVertex, int endVertex, 
    Stack *stack1, Stack *stack2)
{
    int isReachable = 0;
    
    depthFirstSearch(graph, stack1, startVertex);
    resetVisited(graph, graph->vertexCount);
    
    depthFirstSearch(graph, stack2, endVertex);

    for (int i = 0; i < graph->vertexCount; i++)
    {
        if (stack1->array[i] == endVertex && 
            stack2->array[i] == startVertex)
        {
            isReachable = 1;
            break;
        }
    }

    if (isReachable)
    {
        printf("Exista drum intre restaurantele %d si %d\n", 
            startVertex + 1, endVertex + 1);
    }
    else
    {
        printf("Nu exista drum intre restaurantele %d si %d\n", 
            startVertex + 1, endVertex + 1);
    }
}

void checkAllPaths(Graph *graph, Stack *stack1, Stack *stack2)
{
    int *reachableNodes = calloc(graph->vertexCount, sizeof(int));
    if (!reachableNodes) {
        printf("Eroare alocare memorie!\n");
        return;
    }

    for (int i = 0; i < graph->vertexCount; i++)
    {
        for (int j = 0; j < graph->vertexCount; j++)
        {
            stack1->top = -1;
            depthFirstSearch(graph, stack1, i);
            
            resetVisited(graph, graph->vertexCount);
            stack2->top = -1;
            depthFirstSearch(graph, stack2, j);

            for (int k = 0; k < graph->vertexCount; k++)
            {
                for (int l = 0; l < graph->vertexCount; l++)
                {
                    if ((stack1->array[l] == k) && 
                        (stack2->array[k] == l))
                    {
                        reachableNodes[l] = 1;
                    }
                }
            }
        }
    }

    int isFullyConnected = 1;
    for (int i = 0; i < graph->vertexCount; i++)
    {
        if (!reachableNodes[i])
        {
            isFullyConnected = 0;
            break;
        }
    }

    printf("Rezultatul verificarii conectivitatii grafului:\n");
    if (isFullyConnected)
    {
        printf("Toate restaurantele sunt conectate intre ele!\n");
    }
    else
    {
        printf("Nu toate restaurantele sunt conectate intre ele!\n");
    }

    free(reachableNodes);
}

int main()
{
    int vertexCount;
    int edgeCount;

    printf("Cate noduri are graful? ");
    scanf("%d", &vertexCount);

    printf("Cate muchii are graful? ");
    scanf("%d", &edgeCount);

    Graph *graph = createGraph(vertexCount);
    Stack *stack1 = createStack(2 * vertexCount);
    Stack *stack2 = createStack(2 * vertexCount);

    insertEdges(graph, edgeCount, vertexCount);
    
    checkAllPaths(graph, stack1, stack2);

    // Clean up
    free(stack1->array);
    free(stack1);
    free(stack2->array);
    free(stack2);
    free(graph->visitedNodes);
    free(graph->adjacencyLists);
    free(graph);

    return 0;
}