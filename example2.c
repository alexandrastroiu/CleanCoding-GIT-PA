#include <stdlib.h>
#include <stdio.h>

typedef struct node
{
    int data;
    struct node *next;
} NODE;

typedef struct graph
{ 
    int vertices;
    int *visited;
    NODE **adjacencyLists;
} GRAPH;

NODE* createNode(int val)
{
    NODE *new_node = (NODE*)malloc(sizeof(NODE));

    new_node->data = val; 
    new_node->next = NULL;

    return new_node;
}

GRAPH* createGraph(int vertices)
{
    GRAPH *graph = (GRAPH*)malloc(sizeof(GRAPH));

    graph->vertices = vertices;
    graph->adjacencyLists = (NODE**)(malloc(vertices * sizeof(NODE *)));
    graph->visited = (int*)malloc(vertices * sizeof(int));

    for (int i = 0; i < vertices; i++)
    {
        graph->adjacencyLists[i] = NULL;
        graph->visited[i] = 0;
    } 

    return graph;
}

void addEdge(GRAPH *graph, int src, int dest)
{
    NODE *new_node = createNode(dest);

    new_node->next = graph->adjacencyLists[src];
    graph->adjacencyLists[src] = new_node;

    new_node = createNode(src);

    new_node->next = graph->adjacencyLists[dest];
    graph->adjacencyLists[dest] = new_node;
}

void insertEdge(int nrOfVertices, int nrOfEdges, GRAPH *graph)
{ 
    printf("adauga %d muchii (de la 1 la %d)\n", nrOfEdges, nrOfVertices);

    for (int i = 0; i < nrOfEdges; i++)
    {
        int src, dest;

        scanf("%d %d", &src, &dest);
        addEdge(graph, src, dest);
    }
}

int isEmpty(NODE *queue)
{
    return queue == NULL;
}

void enqueue(NODE **queue, int data)
{
    NODE *newNode = createNode(data);

    if (isEmpty(*queue)) 
    {
        *queue = newNode;
    }
    else
    {
       NODE *temp = *queue;

       while(temp->next != NULL)
       {
           temp = temp->next;
       }
       temp->next = newNode;
    } 
}

int dequeue(NODE **queue)
{ 
    NODE *temp = *queue;
    *queue = (*queue)->next;
    int data = temp->data;
  
    return data;
}

void printGraph(GRAPH *graph)
{
    for (int i = 0; i < graph->vertices; i++)
    {
        NODE *temp = graph->adjacencyLists[i];

        printf("%d:", i);
        while (temp != NULL)
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

void wipeVisitedList(GRAPH *graph, int nrOfVertices)
{
    for (int i = 0; i < nrOfVertices;i++)
    {
        graph->visited[i] = 0;
    }
}

// parcurgeri
void DFS(GRAPH *graph, int vertex)
{
    NODE *adjList = graph->adjacencyLists[vertex];
    NODE *temp = adjList;

    graph->visited[vertex] = 1;
    printf("%d ", vertex); 

    while (temp != NULL)
    {
        int connectedVertex = temp->data;

        if (graph->visited[connectedVertex] == 0)
        {
            DFS(graph, connectedVertex);
        }
        temp = temp->next;
    }
}

void BFS(GRAPH *graph, int start)
{
    NODE *queue = NULL;

    graph->visited[start] = 1;
    enqueue(&queue, start);

    while (!isEmpty(queue))
    {
        int current = dequeue(&queue);
        printf("%d ", current);

        NODE *temp = graph->adjacencyLists[current];

            while (temp != NULL)
            {
               int adjVertex = temp->data;

               if(graph->visited[adjVertex] == 0)
               {
                  graph->visited[adjVertex] = 1;
                  enqueue(&queue, adjVertex);
               }
               temp = temp->next;
            }
    }
}

int main()
{

    int nrOfVertices, nrOfEdges, startingVertex;

    printf("Cate noduri are graful?\n");
    scanf("%d", &nrOfVertices);
    printf("Cate muchii are graful?\n");
    scanf("%d", &nrOfEdges);
     
    GRAPH *graph = createGraph(nrOfVertices);

    insertEdge(nrOfVertices, nrOfEdges, graph);
    printf("\nLista de adiacenta:\n");
    printGraph(graph);

    printf("\nDe unde plecam in DFS?\n");
    scanf("%d", &startingVertex);
    printf("\nParcurgere cu DFS:\n");
    DFS(graph, startingVertex);

    wipeVisitedList(graph, nrOfVertices);
    printf("\nDe unde plecam in BFS?\n");
    scanf("%d", &startingVertex);
    printf("\nParcurgere cu BFS:\n");
    BFS(graph, startingVertex);

    return 0;
}
