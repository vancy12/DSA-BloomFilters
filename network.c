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
    //addEdge(graph1, 2, 3);
    //addEdge(graph1, 2, 4);
    addEdge(graph1, 4, 7);
    addEdge(graph1, 4, 6);
    addEdge(graph1, 4, 5);
    addEdge(graph1, 5, 6);
    addEdge(graph1, 5, 3);
    //addEdge(graph1, 3, 7);
    return graph1;
    
}

void print_path(int path[]){
    int i = 0;
    while(path[i]!=-1 && i<9){
        printf("%d ",path[i]);
        i++;
    }
    printf("\n");
}


void dfs(Graph* graph, int vertex, int destination, int path[], int path_index, char digest[]){
    path[path_index]=vertex;
    char *local_str = strdup(digest);
    char changes[2];
    sprintf(changes, "%d", 14+(vertex*vertex));
    strcat(local_str, changes);
    strcat(digest, changes);

    if (vertex == destination) {
        // Destination reached, stop further traversal
        path[path_index]=vertex;
        path[path_index+1]=-1;
        //printf("%d ", vertex);
        bloomFilterSetString(graph->adjLists[vertex]->filter, digest);
        //printf("bloomfiltercheckString for %s: %d\n",digest,bloomFilterCheckString(graph->adjLists[vertex]->filter, digest));
        graph->visited[vertex] = 1;
        strcat(digest, "\0");
        return;
    }
    
    graph->visited[vertex] = 1;

    node* temp = graph->adjLists[vertex];
    while (temp) {
        int adjVertex = temp->num;
        if (graph->visited[adjVertex] == 0) {
            dfs(graph, adjVertex, destination, path, path_index+1, digest);
            //printf("%d ", vertex);
            //printf("%d : %s\n",vertex ,local_str);
            bloomFilterSetString(graph->adjLists[vertex]->filter, local_str);
            //printf("bloomfiltercheckString for %s: %d\n", local_str, bloomFilterCheckString(graph->adjLists[vertex]->filter, local_str));
            if (graph->visited[destination] == 1)
                return;
        }
        temp = temp->next;
    }
    int len = strlen(digest);
    if(len>2){
        digest[len - 2] = '\0';
    }
    return;
}


int dfsBackTrack(Graph* graph, int vertex, char string[], int path[], int path_index, int flag){
    //printf("%d ", vertex);

    // Mark the current vertex as visited
    graph->visited[vertex] = 1;
    path[path_index]=vertex;

    if(bloomFilterCheckString(graph->adjLists[vertex]->filter, string)){
        //printf("inside dfsBackTrack for %s: %d\n", string,bloomFilterCheckString(graph->adjLists[vertex]->filter, string));
        int len = strlen(string);
        if(len>2){
            string[len - 2] = '\0';
        }
        //printf("%s\n",string);
        // If the string is found, continue searching backward
        node* temp = graph->adjLists[vertex];
        while(temp){
            int adjVertex = temp->num;
            // Look for the next vertex containing the string in its Bloom filter
            if(bloomFilterCheckString(graph->adjLists[adjVertex]->filter, string) && !graph->visited[adjVertex]){
                flag = dfsBackTrack(graph, adjVertex, string, path, path_index+1, flag);
                // Once src node is reached, stop further traversal
                if (flag)
                    return flag;
            }
            temp = temp->next;
        }
        flag=vertex;
        path[path_index]=vertex;
        path[path_index+1]=-1;
    }
}

int main() {

    // attack packet digest
    char attack[100]="";
    //printf("DFS traversal starting from vertex 0:\n");

    Graph* graph = createGraph(9);
    graph = formGraph(graph);

    int * path = (int*)malloc(9*sizeof(int));

    dfs(graph, 0, 7, path, 0, attack);
    printf("Printing path: \n");
    print_path(path);
    
    int * path2 = (int*)malloc(sizeof(int)*9);
    for(int i = 0; i < 9; i++){
        graph->visited[i] = 0;
    }
    int src = dfsBackTrack(graph, 7, attack, path2, 0, 0);
    printf("Printing path: \n");
    print_path(path2);
    return 0;
}
