#include <stdio.h>
#include<limits.h>
#define GMAX 10

int A[GMAX][GMAX], n, d[GMAX], p[GMAX];
int BellmanFord(int s) {
    int i, u, v;
    for (i = 1; i < n; i++) {
        for (u = 0; u < n; u++) {
            for (v = 0; v < n; v++) {
                if (d[v] > d[u] + A[u][v]) {
                    d[v] = d[u] + A[u][v];
                    p[v] = u;
                }
            }
        }
    }
    for (u = 0; u < n; u++) {
        for (v = 0; v < n; v++) {
            if (d[v] > d[u] + A[u][v]) {
                printf("Negative Edge\n");
                return 0 ;
            }
        }
    }
    return 1;
}

int main() {
    printf("Enter the no. of vertices\n:");
    scanf("%d", &n);
    printf("Enter the adjacency matrix\n");
    int i, j;
    for (i = 0; i < n; i++)
        for (j = 0; j < n; j++)
            scanf("%d", &A[i][j]);

    int source;
    for (source = 0; source < n; source++) {
        for (i = 0; i < n; i++) {
            d[i] = INT_MAX>>1;//INT_MAX;//INT_MAX;
            p[i] = -1;
        }
        d[source] = 0;

        if(!BellmanFord(source)){
            return 1;
        };

        printf("Router %d\n", source);

        for (i = 0; i < n; i++) {
            if (i != source) {
                j = i;
                while (p[j] != -1) {
                    printf("%d <- ", j);
                    j = p[j];
                }
            }
            printf("%d\tCost %d\n\n", source, d[i]);
        }
    }

    return 0;
}