#include <stdio.h>
#define GMAX 20
#define RTCNT 10

struct node {
    unsigned dist[GMAX];
    unsigned from[GMAX];
} rt[RTCNT];

int main() {
    int costmat[GMAX][GMAX];
    int nodes = 0, i = 0, j = 0, k, count = 0;
    printf("Vertex count\n:");
    scanf("%d", &nodes);  // Enter the nodes
    printf("Enter cost matrix:\n");
    for (i = 0; i < nodes; i++) {
        for (j = 0; j < nodes; j++) {
            scanf("%d", &costmat[i][j]);
            costmat[i][i] = 0;
            rt[i].dist[j] =
                costmat[i][j];  // initialise the distance equal to cost matrix
            rt[i].from[j] = j;
        }
    }
    do {
        count = 0;
        for (i = 0; i < nodes; i++)
            /*
             * Choose arbitary vertex k and calculate the direct
             * distance from the node i to k using the cost matrix
             * and add the distance from k to node j
             */
            for (j = 0; j < nodes; j++)
                for (k = 0; k < nodes; k++)
                    if (rt[i].dist[j] > costmat[i][k] + rt[k].dist[j]) {
                        // We calculate the minimum distance
                        rt[i].dist[j] = rt[i].dist[k] + rt[k].dist[j];
                        rt[i].from[j] = k;
                        count++;
                    }
    } while (count != 0);
    for (i = 0; i < nodes; i++) {
        printf("\n\nVertex %d:", i + 1);
        for (j = 0; j < nodes; j++) {
            printf("\nNode %d via %d: Distance %d ", j + 1, rt[i].from[j] + 1,
                   rt[i].dist[j]);
        }
    }
}