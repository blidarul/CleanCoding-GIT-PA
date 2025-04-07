/*Determinati daca exista sau nu drum direct intre doua restaurante dintr-o retea de tip graf*/

#include <stdlib.h>
#include <stdio.h>

typedef struct Node
{
    int data;
    struct Node *next;
}NODE;
// pentru simplitate, folosim int uri pt a numi restaurantele/locatiile
// ex: 1 - restaurantul 1 si tot asa    

typedef struct Graph
{
    int v;
    int *visited;
    struct Node **alists;
}GRAPH;

typedef struct Stack
{
    int top;
    int cap;
    int *array;
}STACK;

NODE *create_node(int value)
{
    NODE *new_node = malloc(sizeof(NODE));
    
    new_node->data = value;
    new_node->next = NULL;
    return new_node;
}

void add_edge(GRAPH *graph,int source,int destination)
{
    NODE *new_node = create_node(destination);

    new_node->next = graph->alists[source];
    graph->alists[source] = new_node;
    
    new_node = create_node(source);
    
    new_node->next = graph->alists[destination];
    graph->alists[destination] = new_node;
}

GRAPH *createGraph(int v)
{
    int i;
    
    GRAPH *graph = malloc(sizeof(GRAPH));
    
    graph->v = v;
    graph->alists = malloc(sizeof(NODE *));
    graph->visited = malloc(sizeof(int) *v);

    for (int i = 0; i < v; i++)
    {
        graph->alists[i] = NULL;
        graph->visited[i] = 0;
    }    
    return graph;
}

STACK *create_stack(int cap)
{
    STACK *stack = malloc(sizeof(STACK));
    stack->array = malloc(cap * sizeof(int));
    stack->top = -1;
    stack->cap = cap;

    return stack;
}

void push(int pushed, STACK *stack)
{
    stack->top = stack->top + 1;
    stack->array[stack->top] = pushed;
}

void DFS(GRAPH *graph, STACK *stack, int nr_noduri)
{
    NODE *adj_list = graph->alists[nr_noduri];
    NODE *aux = adj_list;

    graph->visited[nr_noduri] = 1;
    printf("%d ", nr_noduri);
    push(nr_noduri, stack);

    while (aux != NULL)
    {
        int nod_conectat = aux->data;

        if (graph->visited[nod_conectat] == 0)
        {
            DFS(graph, stack, nod_conectat);
        }
        aux = aux->next;
    }
}

void insert_edges(GRAPH *graph,int nr_muchii,int nr_noduri)
{
    int src, dest, i;
    printf("adauga %d muchii (de la 1 la %d)(scrie sursa si destinatie)\n",nr_muchii,nr_noduri);

    for (i = 0; i < nr_muchii; i++)
    {
        scanf("%d%d", &src, &dest);
        add_edge(graph,src,dest);
    }
}

void wipe(GRAPH *graph, int nr_noduri)
{
    for (int i = 0;i < nr_noduri; i++)
    {
        graph->visited[i] = 0;
    }
}    

void canbe(GRAPH *graph, int nr_noduri, STACK *stack1, STACK *stack2)
{
    int *canbe = calloc(5, sizeof(int));        // 0 sau 1 daca poate fi sau nu ajuns

    for (int i = 0; i < nr_noduri; i++) // aici i tine loc de numar adica de restaurant
    {
        for (int j = 0; j < 5; j++)
        {
            DFS(graph, stack1, i);
            wipe(graph, nr_noduri);
            DFS(graph, stack2, i);
            for (int j = 0; j < nr_noduri; j++)
            {
                for (int i = 0; i < nr_noduri; i++)
                {
                    if ((stack1->array[i] == j) && (stack2->array[j] == i))
                        *canbe = 1;
                    
                }
            }    
        }
    }
}

int main()
{

    int nr_noduri;
    int nr_muchii;

    printf("cate noduri are graful?");
    scanf("%d", &nr_noduri);

    printf("cate muchii are graful?");
    scanf("%d", &nr_muchii);

    GRAPH *g = createGraph(nr_noduri);

    STACK *s1 = create_stack(2 * nr_noduri);
    STACK *s2 = create_stack(2 * nr_noduri);

    insert_edges(g, nr_muchii, nr_noduri);

    canbe(g, nr_noduri, s1, s2);

    return 0;
}