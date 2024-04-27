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
    NODE **adjacency_lists;
} GRAPH;

/// utils
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
    graph->adjacency_lists = (NODE**)(malloc(vertices * sizeof(NODE *)));
    graph->visited = (int*)malloc(sizeof(int) * vertices);

    for (int i = 0; i < vertices; i++)
    {
        graph->adjacency_lists[i] = NULL;
        graph->visited[i] = 0;
    } 

    return graph;
}

void addEdge(GRAPH *graph, int src, int dest)
{
    NODE *new_node = createNode(dest);

    new_node->next = graph->adjacency_lists[src];
    graph->adjacency_lists[src] = new_node;

    new_node = createNode(src);

    new_node->next = graph->adjacency_lists[dest];
    graph->adjacency_lists[dest] = new_node;
}

void insertEdge(int nr_of_vertices, int nr_of_edges, GRAPH *graph)
{ 
    printf("adauga %d muchii (de la 1 la %d)\n", nr_of_edges, nr_of_vertices);

    for (int i = 0; i < nr_of_edges; i++)
    {
        int src, dest;

        scanf("%d %d", &src, &dest);
        addEdge(graph, src, dest);
    }
}

/// bfs utils
int isEmpty(NODE *queue)
{
    return queue == NULL;
}

void enqueue(NODE **queue, int data)
{
    NODE *new_node = createNode(data);

    if (isEmpty(*queue)) 
    {
        *queue = new_node;
    }
    else
    {
      NODE *temp = *queue;

      while (temp->next != NULL)
      {
         temp = temp->next;
      }
      temp->next = new_node;
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
        NODE *temp = graph->adjacency_lists[i];

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

void wipeVisitedList(GRAPH *graph, int nr_of_vertices)
{
    for (int i = 0; i < nr_of_vertices;i++)
    {
          graph->visited[i] = 0;
    }
}

// parcurgeri
void DFS(GRAPH *graph, int vertex)
{
     NODE *adj_list = graph->adjacency_lists[vertex];
     NODE *temp = adj_list;

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

        NODE *temp = graph->adjacency_lists[current];

            while (temp != NULL)
            {
            int adj_vertex = temp->data;

            if (graph->visited[adj_vertex] == 0)
            {
                graph->visited[adj_vertex] = 1;
                enqueue(&queue, adj_vertex);
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
