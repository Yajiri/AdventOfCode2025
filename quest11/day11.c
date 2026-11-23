#include <stdlib.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define MAX_ROWS 1000
#define MAX_COLS 256

//c doesn't have... classes, constructors, vectors, hashmaps, automatic string handling. So we'll need to work around that.
//typedef struct Node {...} is required because we use Node inside the typdef struct.
typedef struct Node {
    char name[32];
    struct Node *parent;
    struct Node **children;
    int child_count;
} Node;

//typdef struct {...} name; doesn't require a name before the construction block because we are not using it inside the construction block.
typedef struct {
    char from[32];
    char destinations[32][32];
    int destination_count;

} Edge;

//here we don't need the name previous to the construction block becuase we're using the name from a previous construct inside.
typedef struct {
    Edge *edges;
    int edge_count;
} Graph;
//malloc stores the memory on the heap instead of the stack, eliminates the stack overflow possibility from this function, also if I need more memory allocated then
//malloc(size * sizeof(int))
//malloc needs to be instantiated to a pointer, since it returns the location of the memory, and not the memory itself.
Node *create_node(const char *name, Node *parent) {
    Node *node = malloc(sizeof(Node));
    //add this when using malloc, for safety reasons.
    if (node == NULL) {
        exit(1);
    }
    strcpy(node->name, name);

    node->parent = parent;

    node->children = NULL;
    node->child_count = 0;

    return node;
}

void add_child(Node *parent, Node *child) {
    parent ->children = realloc(
            parent -> children,
            sizeof(Node*) * (parent->child_count + 1)
    );

    parent->children[parent->child_count] = child;
    parent->child_count++;
}

bool exist_in_parents(Node *current, const char *target) {
    while (current != NULL) {
        if (strcmp(current->name, target) == 0) {  //strcmp() is used instead of javas .equals()
            return true;
        }
        current = current->parent;
    }
    return false;
}

Edge *find_edge(Graph *graph, const char *name) {
    for (int i = 0; i < graph->edge_count; i++) {
        if (strcmp(graph->edges[i].from, name) == 0) {
            return &graph->edges[i];
        }
    }
    return NULL;
}

//there might be a problem with this one if there are a very deep path > 100 000 then I will get stack overflow, and will need to remedy it.
void search(Node *current, Graph *graph) {
    Edge *edge = find_edge(graph, current->name);
    if (edge == NULL) {
        return;
    }

    for (int move = 0; move < edge->destination_count; move++) {
        if (exist_in_parents(current, edge->destinations[move])) {
            continue;
        }
        Node *child = create_node(edge->destinations[move], current);
        add_child(current, child);
        search(child, graph);
    }
}

void print_tree(Node *node, int depth) {
    for (int i = 0; i < depth; i++) {
        printf(" ");
    }
    printf("%s\n", node->name);
    for (int i = 0; i < node->child_count; i++) {
        print_tree(node->children[i], depth + 1);
    }
}

int count_paths(Node *node) {
    if (strcmp(node->name, "out") == 0) {
        return 1;
    }
    int paths = 0;
    for (int i = 0; i < node->child_count; i++) {
        paths += count_paths(node->children[i]);
    }
    return paths;
}

void free_tree(Node *node) {
    for (int i = 0; i < node->child_count; i++) {
        free_tree(node->children[i]);
    }
    free(node->children);
    free(node);
}

int main(void) {
    
    FILE *fp = fopen("input.txt", "r");
    if (fp == NULL) {
        printf("Can't read this file");
        return 1;
    }
    char grid[MAX_ROWS][MAX_COLS];
    char line [MAX_COLS];
    int rows = 0;

    while (fgets(line, sizeof(line), fp) != NULL) {
        line[strcspn(line, "\n")] = '\0';

        strcpy(grid[rows], line);
        rows++;
    }
    fclose(fp);

    char *start_point = "you";
    int paths = 0;
    Node *root = create_node(start_point, NULL); //here is why we needed to create the function instead of like in Java where we would do a Node root = new Node(startPoint, null);
    //instead of the HashMap initiation we would do in Java it now becomes 
    Graph graph;
    graph.edge_count = rows;
    graph.edges = malloc(sizeof(Edge) * graph.edge_count);

    //grid parse here
    for (int i = 0; i < rows; i++) {
    char buffer[100];
    strcpy(buffer, grid[i]);
    char *from = strtok(buffer, ":");
    char *moves = strtok(NULL, ":");
    strcpy(graph.edges[i].from, from);
    graph.edges[i].destination_count = 0;
    char *move = strtok(moves, " \t\r\n"); //\t removes tabs, \n removes new line, \r this is Carrige Return(CR) historically from typewriters.
    while (move != NULL) {
        strcpy(graph.edges[i].destinations[graph.edges[i].destination_count], move);
        graph.edges[i].destination_count++;
        move = strtok(NULL, " ");
    }
}
graph.edge_count = rows;

    search(root, &graph);
    print_tree(root, paths);
    printf("%d\n", count_paths(root));
    free_tree(root);
    free(graph.edges);
    return 0;
}

