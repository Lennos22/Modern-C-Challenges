/* Created by: Nelson Cardona
 * Start Time/Date: 12:59/15-03-23
 * Completion Time/Date: 16:32/15-03-23
 */
#include <stdlib.h>
#include <stdio.h>

#include <stdint.h>
/* For bool and true/false */
#include <stdbool.h>

/* Copied from Challenge 6 */
void printVector(size_t dim, size_t const vec[dim]) {
	printf("{");
	for (size_t i = 0; i < dim; ++i) {
		printf("%zu", vec[i]);
		if (i < dim - 1)
			printf(", ");
	}
	printf("}\n");
}

/* Do-nothing Breadth-First Search */
void bfs(size_t nElem, bool const graph[nElem][nElem], size_t start) {
	bool visited[nElem];
	size_t queue[nElem];

	for (size_t i = 0; i < nElem; ++i) {
		visited[i] = (i == start);	// Already visited start
	}

	queue[0] = start;
	size_t back = 1;
	for (size_t front = 0; front < nElem; ++front) {
		size_t currNode = queue[front];
		
		printf("Checking node: %zu\n", currNode);
		for (size_t i = 0; i < nElem; ++i) {
			if (graph[currNode][i]) {
				printf("Node %zu is connected to node %zu\n", currNode, i);
				/* Add connected node to queue if not yet visited */
				if (!visited[i]) {
					printf("Node %zu has not yet been visited.\n", i);
					queue[back] = i;
					++back;
					visited[i] = true;
				}
			}
		}

		printf("Finsished checking node %zu. The queue is now:\n{", currNode);
		for (size_t i = 0; i < back; ++i) {
			printf("%zu", queue[i]);
			if (i < back - 1)
				printf(", ");
		}
		printf("}\n");
	}

	printf("Bfs completed! Thanks for playing.\n");
}

/* I thought I could make a recursive bfs algorithm, but it seems like it's
 * only feasible for dfs
 */

void findConnComp(size_t nElem, bool const graph[nElem][nElem], size_t node) {
	bool visited[nElem];
	size_t queue[nElem];

	for (size_t i = 0; i < nElem; ++i) {
		visited[i] = (i == node);	// Already visited node
	}

	queue[0] = node;
	size_t front = 0;
	size_t back = 1;
	while (front < back) {
		size_t currNode = queue[front];
		++front;
		
		for (size_t i = 0; i < nElem; ++i) {
			if (graph[currNode][i] && !visited[i]) {
				queue[back] = i;
				++back;
				visited[i] = true;
			}
		}
	}

	if (back == 1) {
		printf("Node %zu is not connected to any other node on the graph.\n", node);
		return;
	}
	
	printf("The connected components of node %zu are:\n{", node);
	for (size_t i = 1; i < back; ++i) {
		printf("%zu", queue[i]);
		if (i < back - 1)
			printf(", ");
	}
	printf("}\n");
}

void findSpanTree(size_t nElem, bool const graph[nElem][nElem], size_t root, size_t parent[nElem]) {
	bool visited[nElem];
	size_t queue[nElem];

	for (size_t i = 0; i < nElem; ++i) {
		visited[i] = (i == root);	// Already visited root
	}

	queue[0] = root;
	size_t front = 0;
	size_t back = 1;
	while (front < back) {
		size_t currNode = queue[front];
		++front;
		
		for (size_t i = 0; i < nElem; ++i) {
			if (graph[currNode][i] && !visited[i]) {
				parent[i] = currNode;
				queue[back] = i;
				++back;
				visited[i] = true;
			}
		}
	}
}

/* Generates a forest data structure from an adjacency matrix.
 *
 * Uses an algorithm that generates the spanning tree of a node in
 * an acyclical graph. You'll need to initialise the forest object with
 * all elements as their own root.
 *
 * (Again, I still think it would make more sense to roots parents of
 * themselves, but that's just me...)
 */
void createForest(size_t nElem, bool const graph[nElem][nElem], size_t parent[nElem]) {
	for (size_t i = 0; i < nElem; ++i) {
		if (parent[i] == SIZE_MAX)
			findSpanTree(nElem, graph, i, parent);
	}
}

int main(int argc, char* argv[argc+1]) {
	bool graph[10][10] = {
		[0] = {0, 0, 0, 0, 0, 0, 0, 1, 0, 0},
		[1] = {0, 0, 1, 0, 1, 0, 0, 1, 0, 0},
		[2] = {0, 1, 0, 0, 1, 0, 0, 0, 0, 0},
		[3] = {0, 0, 0, 0, 0, 1, 1, 0, 0, 0},
		[4] = {0, 1, 1, 0, 0, 0, 0, 1, 0, 0},	// Using ints here for CLARITY
		[5] = {0, 0, 0, 1, 0, 0, 0, 1, 1, 1},	// Notice how matrix is symmetric
		[6] = {0, 0, 0, 1, 0, 0, 0, 1, 0, 1},
		[7] = {1, 1, 0, 0, 1, 1, 1, 0, 0, 0},
		[8] = {0, 0, 0, 0, 0, 1, 0, 0, 0, 0},
		[9] = {0, 0, 0, 0, 0, 1, 1, 0, 0, 0},
		};

	printf("Perfoming bfs on first graph:\n");
	bfs(10, graph, 1);

	printf("\nUsing graph 2\n");
	bool graph2[15][15] = {
		[0] = {[6] = true},
		[1] = {[7] = true},
		[2] = {[6] = true, [11] = true},
		[3] = {[7] = true,},
		[4] = {[9] = true},
		[5] = {0},
		[6] = {[0] = true, [2] = true, [11] = true},
		[7] = {[1] = true, [3] = true,},
		[8] = {[10] = true, [12] = true, [13] = true, [14] = true},
		[9] = {[4] = true, [11] = true,},
		[10] = {[8] = true},
		[11] = {[2] = true, [6] = true, [9] = true},
		[12] = {[8] = true},
		[13] = {[8] = true},
		[14] = {[8] = true},
	};

	printf("Finding connected components of 1\n");
	findConnComp(15, graph2, 1);
	printf("Finding connected components of 0\n");
	findConnComp(15, graph2, 0);
	printf("Finding connected components of 5\n");
	findConnComp(15, graph2, 5);
	printf("Finding connected components of 10\n");
	findConnComp(15, graph2, 10);

	printf("\nConverting graph 2 into a forest:\n");
	size_t graph2Parent[15] = {0};
	for (size_t i = 0; i < 15; ++i)
		graph2Parent[i] = SIZE_MAX;

	createForest(15, graph2, graph2Parent);
	printVector(15, graph2Parent);

	return EXIT_SUCCESS;
}

