
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#define MAX_POINTS 1000
#define MAX_EDGES 1000

//had massive problems with my stack overflowing... need to learn more about this.
int graph[MAX_POINTS][MAX_EDGES];
int degree_global[MAX_POINTS];
bool visited_global[MAX_POINTS];
int sizes_global[MAX_POINTS];
int stack_global[MAX_POINTS];

int read_points_from_file(const char *filename, int points[][3], int max_points) {
    FILE *f = fopen(filename, "r");
    if (!f) {
        perror("fopen");
        return -1;
    }
    char line[256];
    int count = 0;

    while (count < max_points && fgets(line, sizeof(line), f) != NULL) {
        int x, y, z;

        if (sscanf(line, "%d,%d,%d", &x, &y, &z) == 3) {
            points[count][0] = x;
            points[count][1] = y; 
            points[count][2] = z;
            count++;
        }
    }
    fclose(f);
    return count;
}

struct Pair {
    long long distance;
    int i;
    int j;
};

long long dist2(int a[3], int b[3]) {
    long long dx = a[0] - b[0];
    long long dy = a[1] - b[1];
    long long dz = a[2] - b[2];

    return dx * dx + dy * dy + dz * dz;
}

int comparePairs(const void *a, const void *b)
{
    const struct Pair *pa = (const struct Pair *)a;
    const struct Pair *pb = (const struct Pair *)b;

    if (pa->distance < pb->distance) return -1;
    if (pa->distance > pb->distance) return 1;
    return 0;
}

int getShortest1000(int points[][3], int num_points, struct Pair result[MAX_EDGES]) {

    long long num_pairs_ll = (long long)num_points * (num_points - 1) / 2;
    int num_pairs = (num_pairs_ll > 1000000) ? 1000000 : (int)num_pairs_ll; // safety cap

    struct Pair *pairs = malloc(num_pairs * sizeof(struct Pair));
    if (!pairs) {
        fprintf(stderr, "malloc failed for pairs\n");
        return 0;
    }

    int pairCount = 0;
    for (int i = 0; i < num_points; i++) {
        for (int j = i + 1; j < num_points; j++) {
            if (pairCount >= num_pairs) break;
            pairs[pairCount].distance = dist2(points[i], points[j]);
            pairs[pairCount].i = i;
            pairs[pairCount].j = j;
            pairCount++;
        }
    }

    qsort(pairs, pairCount, sizeof(struct Pair), comparePairs);

    int count = pairCount < MAX_EDGES ? pairCount : MAX_EDGES;
    for (int k = 0; k < count; k++) {
        result[k] = pairs[k];
    }

    free(pairs);
    return count;  // number of edges we actually return (<=1000)
}

int compare_int_desc(const void *a, const void *b) {
        int ia = *(const int *)a;
        int ib = *(const int *)b;
        if (ia > ib) return -1;
        if (ia < ib) return 1;
        return 0;
}

long long solution(int points[][3], int num_points) {
    struct Pair edges[MAX_EDGES];
    int edge_count = getShortest1000(points, num_points, edges);

    // initialize degrees and visited
    for (int i = 0; i < num_points; i++) {
        degree_global[i] = 0;
        visited_global[i] = false;
    }

    // build graph from ALL edges
    for (int k = 0; k < edge_count; k++) {
        int u = edges[k].i;
        int v = edges[k].j;

        graph[u][degree_global[u]++] = v;
        graph[v][degree_global[v]++] = u;
    }

    int sizes_count = 0;

    for (int start = 0; start < num_points; start++) {
        if (visited_global[start]) continue;

        int top = -1;
        stack_global[++top] = start;

        int size = 0;

        while (top >= 0) {
            int node = stack_global[top--];
            if (visited_global[node]) continue;
            visited_global[node] = true;
            size++;

            for (int i = 0; i < degree_global[node]; i++) {
                int neighbor = graph[node][i];
                if (!visited_global[neighbor]) {
                    stack_global[++top] = neighbor;
                }
            }
        }

        sizes_global[sizes_count++] = size;
    }

    if (sizes_count < 3) {
        return 0;
    }
    
    qsort(sizes_global, sizes_count, sizeof(int), compare_int_desc);
    long long result = (long long)sizes_global[0] * sizes_global[1] * sizes_global[2];
    return result;
}

int main(void) {
    int points[MAX_POINTS][3];
    int num_points = read_points_from_file("input.txt", points, MAX_POINTS);
    printf("num_points = %d\n", num_points);

    if(num_points <= 0) {
        printf("No points found in .txt file\n");
        return 1;
    }

    long long ans = solution(points, num_points);
    printf("solution = %lld\n", ans);
    return 0;
}
