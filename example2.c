/* parcurgerge  graf cu DFS/BFS */

#include <stdlib.h>
#include <stdio.h>

typedef struct Node
{
    int data;
    struct Node *next;
}NODE;

typedef struct Graph
{ 
    int vertexCount;
    int *visitedNodes;
    struct Node **adjacencyLists;
}GRAPH;


NODE *createNode(int value)
{ 
    NODE *newNode = malloc(sizeof(NODE));
    newNode->data = value;
    newNode->next = NULL;
    return newNode;
}

GRAPH *createGraph(int vertexCount)
{
    GRAPH *graph = malloc(sizeof(GRAPH));
    graph->vertexCount = vertexCount;
    graph->adjacencyLists = (NODE **)malloc((size_t)vertexCount * sizeof(NODE *));
    graph->visitedNodes = (int *)malloc((size_t)vertexCount * sizeof(int));
    
    for (int i = 0; i < vertexCount; i++)
    {
        graph->adjacencyLists[i] = NULL;
        graph->visitedNodes[i] = 0;
    } 
    
    return graph;
}

void addEdge(GRAPH *graph, int source, int destination)
{
    NODE *new_node = createNode(destination);
    new_node->next = graph->adjacencyLists[source];
    graph->adjacencyLists[source] = new_node;

    new_node = createNode(source);
    new_node->next = graph->adjacencyLists[destination];
    graph->adjacencyLists[destination] = new_node;
}

void insertEdges(int vertexCount, int edgeCount, GRAPH *graph)
{ 
    int source, destination, i;
    printf("adauga %d muchii (de la 1 la %d)\n", edgeCount, vertexCount);
    for (i = 0; i < edgeCount; i++)
    {
        scanf("%d%d", &source, &destination);
        addEdge(graph, source, destination);
    }
}

int isEmpty(NODE *queue)
{
    return queue == NULL;
}

void enqueue(NODE **queue, int data)
{
    NODE *new_node = createNode(data);

    if (isEmpty(*queue))
        *queue = new_node;
    else
    {
        NODE *temp = *queue;
        while (temp->next)
        {
            temp = temp->next;
        }
        temp->next = new_node;
    }
}

int dequeue(NODE **queue)
{
    int data = (*queue)->data;
    NODE *temp = *queue;
    *queue = (*queue)->next;
    free(temp);
    return data;
}

void printGraph(GRAPH *graph)
{
    int i;
    for (i = 0; i < graph->vertexCount; i += 1)
    {
        NODE *temp = graph->adjacencyLists[i];

        while (temp) 
        {
            printf("%d ", temp->data);
            temp = temp->next;
        }
        printf("\n");
    }
}

void printQueue(NODE *queue)
{
    while (queue != NULL)
    {
        printf("%d ", queue->data);
        queue = queue->next;
    }
}

void resetVisitedNodesList(GRAPH *graph, int vertexCount)
{
    for (int i = 0; i < vertexCount; i++)
    {
        graph->visitedNodes[i] = 0;
    }
}

void depthFirstSearch(GRAPH *graph, int currentVertex)
{
    NODE *adjancencyList = graph->adjacencyLists[currentVertex];
    NODE *currentNode = adjancencyList;

    graph->visitedNodes[currentVertex] = 1;
    printf("%d->", currentVertex);

    while (currentNode != NULL)
    {
        int neighborVertex = currentNode->data;

        if (graph->visitedNodes[neighborVertex] == 0)
        {
            depthFirstSearch(graph, neighborVertex);
        }
        currentNode = currentNode->next;
    }
}

void breadthFirstSearch(GRAPH *graph, int startVertex)
{
    NODE *queue = NULL;
    graph->visitedNodes[startVertex] = 1;
    enqueue(&queue, startVertex);

    while (!isEmpty(queue))
    {
        int currentVertex = dequeue(&queue);
        printf("%d ", currentVertex);

        NODE *currentNode = graph->adjacencyLists[currentVertex];
        while (currentNode)
        {
            int neighborVertex = currentNode->data;

            if (graph->visitedNodes[neighborVertex] == 0)
            {
                graph->visitedNodes[neighborVertex] = 1;
                enqueue(&queue, neighborVertex);
            }

            currentNode = currentNode->next;
        }
    }
}

int main()
{
    int vertexCount;
    int edgeCount;
    int startVertex;

    printf("Cate noduri are graful? ");
    scanf("%d", &vertexCount);
    
    printf("Cate muchii are graful? ");
    scanf("%d", &edgeCount);

    GRAPH *graph = createGraph(vertexCount);

    insertEdges(vertexCount, edgeCount, graph);
    
    printf("\nDe unde plecam in Depth First Search? ");
    scanf("%d", &startVertex);

    printf("parcurgere cu Depth First Search: ");
    depthFirstSearch(graph, startVertex);

    resetVisitedNodesList(graph, vertexCount);
    printf("\n");
    
    printf("De unde plecam in Breadth First Search? ");
    scanf("%d", &startVertex);

    printf("Parcurgere cu Breadth First Search: ");
    breadthFirstSearch(graph, startVertex);
    printf("\n");

    return 0;
}