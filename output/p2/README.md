# Program 2 - Dist vector routing (Bellman Ford Algorithm)

## TOC
- [Program 2 - Dist vector routing (Bellman Ford Algorithm)](#program-2---dist-vector-routing-bellman-ford-algorithm)
  - [TOC](#toc)
  - [Program Description](#program-description)
  - [Output](#output)
    - [Graph 1 (3 vertices)](#graph-1-3-vertices)
    - [Graph 2 (5 vertices)](#graph-2-5-vertices)

## Program Description

This algorithm can be used to find the shortest path between two nodes in a weighted graph. Compared to Djikstra's algorithm, it is able to work with negative edges also, but also cannot converge for cycles with a negative edge.

## Output

### Graph 1 (3 vertices)

It can be seen that it does not use edge 1->3 as it yields a longer path

![Simple](Screenshot%20from%202021-01-13%2016-24-59.png)

### Graph 2 (5 vertices)

Infinity is denoted in this program as any number greater than the sum of the absolute values of weights of all the edges in the program. Here, it is denoted as 999. This also implies that the two nodes are unconnected.
As the program here generated the distances for all possible starting nodes, there is a lot of output. 

![Complex](Screenshot%20from%202021-01-13%2016-25-46.png)