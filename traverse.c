#include <stdio.h>
#include <stdlib.h>
#define FALSE -2147483647
#define TRUE 2147483647
typedef struct{
    int* items;
    int MAX_SIZE;
    int top;
}Stack;
Stack* create_stack(int n){
    Stack* stack=(Stack*)malloc(sizeof(Stack));
    if (stack==NULL){
        printf("memory allocation fail");
        exit(-1);
    }
    stack->items = (int*)malloc(n*sizeof(int));
    stack->top=-1;
    stack->MAX_SIZE = n;
    return stack;
}
int is_empty(Stack* stack){
    return stack->top==-1;
}

int is_full(Stack* stack){
    return stack->top==stack->MAX_SIZE-1;
}
int  push(Stack* stack, int item){
    if (is_full(stack)){
        printf("Stack is Full, Cannot push %d. \n",item);
        return FALSE;
    }else{
        stack->items[++stack->top]=item;
        return TRUE;
    }
}
int pop(Stack* stack){
    if (is_empty(stack)){
        printf("Stack is empty, Cannot pop, \n");
        return FALSE;
    }
    return stack->items[stack->top--];
}
int peek(Stack* stack){
    if (is_empty(stack)){
       printf("Stack is empty, Cannot peek \n");
       return FALSE; 
    }
    return stack->items[stack->top];
}
int get_size(Stack* stack){
    return stack->top+1;
}
void destroy_stack(Stack* stack){
    free(stack);
}


typedef struct
{
    int* items;
    int front;
    int rear;
    int size;
} Queus;
Queus *create_queus(int n)
{
    Queus *queue = (Queus *)malloc(sizeof(Queus));
    if (queue == NULL)
    {
        printf("memory allocation fail");
        exit(-1);
    }
    queue->items = malloc(sizeof(int)*n);
    queue->front = -1;
    queue->rear = -1;
    queue->size = n;
    return queue;
}
int isEmpty(Queus *queue)
{
    return queue->front == -1;
}

int isFull(Queus *queue)
{
    return (queue->rear + 1)%queue->size ==  queue->front;
}
int getSize(Queus *queue){
    if (queue->rear > queue->front){
        return queue->rear - queue->front +1;
    }
    else if (queue->rear < queue->front){
        return queue->size-(queue->front - queue->rear +1);
    }
    return 0;
}
int enqueu(Queus *queue, int value)
{
    if (isFull(queue))
    {
        printf("queus is Full, Cannot enque %d. \n", value);
        return FALSE;
    }    
    else
    {
        if (queue->front == -1){
            queue->front = 0;
        }
        queue->items[++queue->rear] = value;
        queue->rear %= queue->size;
        return TRUE;
    }
}
int dequeu(Queus *queue)                                                                                                                                                                                                                        
{
    if (isEmpty(queue))
    {
        printf("queus is empty, Cannot deque \n");
        return FALSE;
    }
    int data=queue->items[queue->front];
    if (queue->rear == queue->front){
        queue->front = -1; 
        queue->rear = -1;
    }else{
        queue->front++;
        queue->front %= queue->size;
        
    }
    return data;
}
void destroy_queus(Queus *queus)
{
    free(queus);
}




struct Node {
    int data;
    struct Node* next;
};


struct AdjList {
    struct Node* head;
};

struct Graph {
    int V; 
    struct AdjList* array;
};

struct Node* NewNode(int data) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

struct Graph* createGraph(int V) {
    struct Graph* graph = (struct Graph*)malloc(sizeof(struct Graph));
    graph->V = V;
    graph->array = (struct AdjList*)malloc(V * sizeof(struct AdjList));
    for (int i = 0; i < V; ++i)
        graph->array[i].head = NULL;
    return graph;
}

void addEdge(struct Graph* graph, int v1, int v2) {

    struct Node* newnode = NewNode(v2);
    newnode->next = graph->array[v1].head;
    graph->array[v1].head = newnode;

    newnode = NewNode(v1);
    newnode->next = graph->array[v2].head;
    graph->array[v2].head = newnode;


}

void printGraph(struct Graph* graph) {
    for (int i = 0; i < graph->V; ++i) {
        struct Node* temp = graph->array[i].head;
        printf("%d -> ", i);
        while (temp) {
            printf("%d -> ", temp->data);
            temp = temp->next;
        }
        printf("NULL\n");
    }
}
void traverse_dfs_iterative(struct Graph* graph, int start_vertex){
    Stack* stack=create_stack(graph->V);
    int* visited=calloc(graph->V,sizeof(int));
    push(stack,start_vertex);
    int curVertex;
    while (! is_empty(stack)){
        curVertex=pop(stack);
        if (!visited[curVertex]){
            visited[curVertex] = 1;
            printf("visited %d \n",curVertex);
            struct Node* temp =graph->array[curVertex].head;
            while (temp!=NULL){
                if (!visited[temp->data]){
                    push(stack,temp->data);
                }
                temp=temp->next;
            }
        }
        
    }
}
int traverse_bfs_iterative(struct Graph* graph, int start_vertex){
    int curVertex;
    int visited[graph->V];
    for (int i = 0; i<graph->V; i++){
        visited[i] = 0;
    }
    Queus* queus = create_queus(graph->V);
    visited[start_vertex] = 1;
    enqueu(queus, start_vertex);
    while (! isEmpty(queus)){
        curVertex = dequeu(queus);
        printf("Visited %d\n",curVertex);

        struct Node* temp= graph->array[curVertex].head;
        while (temp != NULL){
            if (! visited[temp->data]){
                visited[temp->data] = 1;
                enqueu(queus, temp->data);
            }
            temp = temp->next;
        }
    }
    return 0;
}



int main(){
    struct Graph* graph = createGraph(5);
    addEdge(graph, 0, 1);
    addEdge(graph, 0, 2);
    addEdge(graph, 0, 3);
    addEdge(graph, 2, 1);
    addEdge(graph, 1, 4);
    printGraph(graph);
    printf("BFS Traversal\n");
    traverse_bfs_iterative(graph, 0);
    printf("DFS Traversal\n");
    traverse_dfs_iterative(graph, 0);
    return 0;
}
