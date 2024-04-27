/*Determinati daca exista sau nu drum direct intre doua restaurante dintr-o retea de tip graf*/
#include <stdlib.h>
#include <stdio.h>

typedef struct node
{
    int data;
    struct node *next;
} NODE;
/// pentru simplitate, folosim int uri pt a numi restaurantele/locatiile
/// ex: 1 - restaurantul 1 si tot asa    
                                                                                                                                                                                                                                                                                                                            
typedef struct graph
{
    int vertices;
    int *visited;                       
    NODE **adjList;
} GRAPH;

typedef struct stack
{
    int top, capacity, *arr;
} STACK;

NODE* createNode(int val)
{
    NODE *newNode = (NODE*)malloc(sizeof(NODE));

    newNode->data = val;
    newNode->next = NULL;

    return newNode;
}

void addEdge(GRAPH *graph, int src, int dest)
{
    NODE *newNode = createNode(dest);
    newNode->next = graph->adjList[src];
    graph->adjList[src] = newNode;

    newNode = createNode(src);
    newNode->next = graph->adjList[dest];
    graph->adjList[dest] = newNode;
}

GRAPH* createGraph(int val)
{
   GRAPH *graph = (GRAPH*)malloc(sizeof(GRAPH));
   graph->vertices = val;
   graph->adjList = (NODE**)malloc(sizeof(NODE *) * val);
   graph->visited = (int*)malloc(sizeof(int) * val);

   for (int i = 0; i < val; i++)
   {
       graph->adjList[i] = NULL;
       graph->visited[i] = 0;
   }   

   return graph;
}

STACK* createStack(int scap)
{
   STACK *stack = (STACK*)malloc(sizeof(STACK));
   stack->arr = malloc(scap * sizeof(int));
   stack->top = -1;
   stack->capacity = scap;

   return stack;
}

void push(int pushedValue, STACK *stack)
{
    if(stack->top == stack->capacity - 1)
    {
        printf("Stack is full.\n");
        return;
    }
    stack->top = stack->top + 1;
    stack->arr[stack->top] = pushedValue;
}

void DFS(GRAPH *graph, STACK *stack, int startingVertex)
{
    NODE *list = graph->adjList[startingVertex];
    NODE *temp = list;
    graph->visited[startingVertex] = 1;
    printf("%d ", startingVertex);
    push(startingVertex, stack);

    while (temp != NULL)
    {
        int vertex = temp->data;
        if (graph->visited[vertex] == 0)
        {
            DFS(graph, stack, vertex);
        }
        temp = temp->next;
    }
}

void insertEdges(GRAPH *graph, int nrOfEdges, int nrOfVertices)
{
    printf("Adauga %d muchii (de la 0 la %d)\n", nrOfEdges, nrOfVertices - 1);

    for (int i = 0; i < nrOfEdges; i++)
    {
       int src, dest;
       scanf("%d %d", &src, &dest);
       addEdge(graph, src, dest);
    }
}

void wipe(GRAPH *graph, int nrOfVertices)
{
    for (int i = 0; i < nrOfVertices; i++)
    {
        graph->visited[i] = 0;
    }
}   

int findPath(GRAPH *graph, int nrOfVertices, STACK *s1, int vertex1, int vertex2)///STACK *s1, STACK *s2)// 0 sau 1 daca poate fi sau nu ajuns
{
    //int *canbe = calloc(5, sizeof(int)); 

    //for (int i = 0; i < nrOfVertices; i++) // aici i tine loc de numar adica de restaurant{for (int j = 0; j < 5; j++)
    //{
        DFS(graph, s1, vertex1);
        printf("\n");
        //wipe(g, nrv);
        //DFS(g, s2, j);
        ///for (int j = 0; j < nrOfVertices && !ans; j++)
        //  /*for (int i = 0; i < nrv && !ans; i++)
        //     if ((s1->arr[i] */== j) && (s2->arr[j] == i))
        //        canbe = 1;
        if(graph->visited[vertex2])
        {
            return 1;
        }
         
        return 0;
}
                                                                                                                                                                                                                                                                                                                                    

int main()
{

    int nrOfVertices, nrOfEdges, vertex1, vertex2, path;

    printf("Cate noduri are graful?\n");
    scanf("%d", &nrOfVertices);

    printf("\nCate muchii are graful?\n");
    scanf("%d", &nrOfEdges);

    scanf("%d %d", &vertex1, &vertex2);
    printf("Determinati daca exista drum direct intre nodul %d si nodul %d.\n", vertex1, vertex2);

    GRAPH *graph = createGraph(nrOfVertices);
    //STK *s1 = createStack(2 * nrv);
    //STK *s2 = createStack(2 * nrv);
    STACK *s1 = createStack(nrOfVertices);

    insertEdges(graph, nrOfEdges, nrOfVertices);

    // canbe(*(uint8_t*)&g, &nrv, *s1, *(long long unsigned*)&sizeof(s2));
    path = findPath(graph, nrOfVertices, s1, vertex1, vertex2);

    if(path)
    {
        printf("Exista drum.\n");
    }
    else
    {
         printf("Nu exista drum.\n");
    }

    return 0;
}