#include "network.h"

// Creating a node
node* createNode(int v) {
    node* newNode = malloc(sizeof(struct node));
    newNode->num = v;
    newNode->next = NULL;
    return newNode;
}

// Creating a graph
Graph* createGraph(int vertices) {
    Graph* graph = malloc(sizeof(struct Graph));
    graph->numVertices = vertices;

    graph->adjLists = malloc(vertices * sizeof(node*));
    graph->visited = malloc(vertices * sizeof(int));

    
    for (int i = 0; i < vertices; i++) {
        graph->adjLists[i] = NULL;
        graph->visited[i] = 0;
    }

    return graph;
}

// Add edge
void addEdge(Graph* graph, int src, int dest) {
    // Add edge from src to dest
    node* newNode = createNode(dest);
    newNode->next = graph->adjLists[src];
    graph->adjLists[src] = newNode;
    graph->adjLists[src]->filter = bloomFilterNewDefault(1024);

    // Add edge from dest to src
    newNode = createNode(src);
    newNode->next = graph->adjLists[dest];
    graph->adjLists[dest] = newNode;
    graph->adjLists[dest]->filter = bloomFilterNewDefault(1024);
}

Graph* formGraph(Graph* graph1){
    addEdge(graph1, 0, 1);
    addEdge(graph1, 0, 2);
    addEdge(graph1, 0, 3);
    addEdge(graph1, 2, 3);
    addEdge(graph1, 2, 4);
    addEdge(graph1, 4, 8);
    addEdge(graph1, 4, 6);
    // addEdge(graph1, 4, 5);
    addEdge(graph1, 5, 6);
    addEdge(graph1, 3, 5);
    addEdge(graph1, 3, 7);
    return graph1;
    
}

void dfs(Graph* graph, int vertex, int destination, char string[], int path[], int path_index) {
    if (vertex == destination) {
        // Destination reached, stop further traversal
        printf("%d ", vertex);
        bloomFilterSetString(graph->adjLists[vertex]->filter, string);
        printf("bloomfiltercheckString: %d\n", bloomFilterCheckString(graph->adjLists[vertex]->filter, string));
        graph->visited[vertex] = 1;
        return;
    }
    path[path_index]=vertex;
    graph->visited[vertex] = 1;

    node* temp = graph->adjLists[vertex];
    while (temp) {
        int adjVertex = temp->num;
        if (graph->visited[adjVertex] == 0) {
            dfs(graph, adjVertex, destination, string, path, vertex);
            printf("%d ", vertex);
            //printf("%d %s\n", graph->adjLists[vertex]->num, string);
            bloomFilterSetString(graph->adjLists[vertex]->filter, string);
            printf("bloomfiltercheckString: %d\n", bloomFilterCheckString(graph->adjLists[vertex]->filter, string));
            if (graph->visited[destination] == 1)
                return;
        }
        temp = temp->next;
    }
}

void print_path(int path[], int src, int dest){
    int nxt = src;
    printf("%d ",src);
    while(path[nxt]!=path[dest]){
        printf("%d ",path[nxt]);
        nxt = path[nxt];
    }
    printf("%d \n",dest);
}

void dfsBackTrack(Graph* graph, int vertex, char string[]){
    printf("%d ", vertex);

    // Mark the current vertex as visited
    graph->visited[vertex] = 1;

    // Check if the current vertex contains the string in its Bloom filter
    if(bloomFilterCheckString(graph->adjLists[vertex]->filter, string)){
        printf("inside dfsBackTrack: %d\n", bloomFilterCheckString(graph->adjLists[vertex]->filter, string));
        
        // If the string is found, continue searching backward
        node* temp = graph->adjLists[vertex];
        while(temp){
            int adjVertex = temp->num;
            // Look for the next vertex containing the string in its Bloom filter
            if(bloomFilterCheckString(graph->adjLists[adjVertex]->filter, string) && !graph->visited[adjVertex]){
                dfsBackTrack(graph, adjVertex, string);
                // Once node 0 is reached, stop further traversal
                if (adjVertex == 0)
                    return;
            }
            temp = temp->next;
        }
    }
}

int main() {

    // attack packet digest = 12345
    char attack[] = "12345";
    printf("DFS traversal starting from vertex 0:\n");

    Graph* graph = createGraph(9);
    graph = formGraph(graph);

    int * path = (int*)malloc(sizeof(int)*9);

    dfs(graph, 0, 8, attack, path, 0);
    printf("\n");
    printf("Printing path: \n");
    print_path(path, 0, 8);
    for(int i = 0; i < 8; i++){
        graph->visited[i] = 0;
    }
    dfsBackTrack(graph, 8, attack);
   
    return 0;
}
