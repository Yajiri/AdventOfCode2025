#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

int points[20][3] = {
        {162,817,812},
        {57,618,57},
        {906,360,560},
        {592,479,940},
        {352,342,300},
        {466,668,158},
        {542,29,236},
        {431,825,988},
        {739,650,466},
        {52,470,668},
        {216,146,977},
        {819,987,18},
        {117,168,530},
        {805,96,715},
        {346,949,466},
        {970,615,88},
        {941,993,340},
        {862,61,35},
        {984,92,344},
        {425,690,689}
};

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
    const struct Pair *pa = a;
    const struct Pair *pb = b;

    return pa->distance - pb->distance;
}

void getShortest10 (int points[][3], int num_points, struct Pair result[10]) {
            struct Pair pairs[190];
            int pairCount = 0;
            for (int i = 0; i < num_points; i++) {
                for (int j = i + 1; j < num_points; j++) {
                    pairs[pairCount++] = (struct Pair){
                        dist2(points[i], points[j]),
                        i,
                        j
                    };
                }
            }

        qsort(pairs, pairCount, sizeof(struct Pair), comparePairs);
        int count = pairCount < 10 ? pairCount : 10;
        for (int i = 0; i < count; i++) {
            result[i] = pairs[i];
        }

    for (int k = 0; k < 10; k++) {
        struct Pair p = pairs[k];

        printf("%d,%d,%d <-> %d,%d,%d distance^2 = %lld\n",
        points[p.i][0], points[p.i][1], points[p.i][2],
        points[p.j][0], points[p.j][1], points[p.j][2],
        p.distance);
    }
}

int compare_int_desc(const void *a, const void *b) {
        int ia = *(const int *)a;
        int ib = *(const int *)b;
        if (ia > ib) return -1;
        if (ia < ib) return 1;
        return 0;
}

int solution(int points[][3], int num_points) {
        struct Pair pairs[10];
        getShortest10(points, num_points, pairs);

        int graph[20][20];
        int degree[20] = {0};

        for (int k = 0; k < 10; k++ ) {
            int u = pairs[k].i;
            int v = pairs[k].j;
            graph[u][degree[u]++] = v;
            graph[v][degree[v]++] = u;
        }

        bool visited[20] = { false };
        int sizes[20];
        int sizes_count = 0;

    for (int start = 0; start < num_points; start++) {
        if (visited[start]) continue;

        int stack [20];
        int top = -1;
        stack[++top] = start;

        int size = 0;

        while (top >= 0) {
            int node = stack[top--];
            if (visited[node]) continue;
            visited[node] = true;
            size++;

        for (int i = 0; i < degree[node]; i++) {
            int neighbor = graph[node][i];
            if(!visited[neighbor]) {
                stack[++top] = neighbor;
                }
            }
        }
        sizes[sizes_count++] = size;
    }

    if(sizes_count < 3) {
        return 0;

    }
    
    qsort(sizes, sizes_count, sizeof(int), compare_int_desc);
    return sizes[0] * sizes[1] * sizes[2];
}

int main(void) {
    struct Pair result[10];
    int ans = solution(points, 20);
    printf("solution = %d\n", ans);
    return 0;
}