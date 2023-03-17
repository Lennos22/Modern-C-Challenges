/* Created by: Nelson Cardona
 * Start Time/Date: 13:23/17-03-23
 * Completion Time/Date: 15:26/17-03-23
 */
#include <stdlib.h>
#include <stdio.h>

#include <stdbool.h>
#include <stdint.h>

/* Get unvisited node w/ shortest distance */
size_t minNodeDist(size_t nElem, size_t dist[nElem], bool visited[nElem]) {
	size_t node = 0;

	while (visited[node])
		++node;

	for (size_t i = node + 1; i < nElem; ++i) {
		if (!visited[i] && dist[i] < dist[node])
			node = i;
	}

	return node;
}

/* Computes the shortest path between two nodes */
size_t shortestPath(size_t nElem, size_t graph[nElem][nElem], size_t start, size_t end) {
	bool visited[nElem];	// This will be processed slightly differently from bfs
	size_t dist[nElem];		// Tentative minimum distances from start to every other node
	size_t queue[nElem];
	queue[0] = start;

	for (size_t i = 0; i < nElem; ++i) {
		visited[i] = 0;
		dist[i] = (i == start) ? 0 : SIZE_MAX;
	}

	while (minNodeDist(nElem, dist, visited) != end) {
		size_t currNode = minNodeDist(nElem, dist, visited);
		if (dist[currNode] == SIZE_MAX)
			return SIZE_MAX;	// Every unvisited node is disconnected!!!
		
		for (size_t i = 0; i < nElem; ++i) {
			if (graph[currNode][i] == SIZE_MAX)
				continue;
			size_t currDist = dist[currNode] + graph[currNode][i];

			if (!visited[i] && (currDist < dist[i]))
				dist[i] = currDist;
		}
		visited[currNode] = true;
	}

	return dist[end];
}

int main(int argc, char* argv[argc+1]) {
	if (argc < 3) {
		printf("Arguments for this program are:\n");
		printf("Start node and end node (between 0-14, inc.)\n");
		return EXIT_FAILURE;
	}
	size_t distGraph[16][16] = {
		[0] = {[5] = 25, [13] = 30, [15] = 3},
		[1] = {[3] = 1, [9] = 12, [12] = 1},
		[2] = {[7] = 123},
		[3] = {[1] = 1, [4] = 5, [6] = 14, [8] = 8},
		[4] = {[3] = 5},
		[5] = {[0] = 25, [10] = 6},
		[6] = {[3] = 14},
		[7] = {[2] = 123},
		[8] = {[3] = 8, [9] = 5, [11] = 3},
		[9] = {[1] = 12, [8] = 5, [12] = 2},
		[10] = {[5] = 6, [13] = 84, [14] = 110},
		[11] = {[8] = 3},
		[12] = {[1] = 1, [9] = 2},
		[13] = {[0] = 30, [10] = 84, [15] = 9},
		[14] = {[10] = 110},
		[15] = {[0] = 3, [13] = 9},
	};

	/* This shit is so annoying */
	for (size_t i = 0; i < 16; ++i) {
		for (size_t j = 0; j < 16; ++j) {
			if (!distGraph[i][j])
				distGraph[i][j] = SIZE_MAX;
		}
	}

	size_t start = strtoull(argv[1], 0, 10);
	size_t end = strtoull(argv[2], 0, 10);

	size_t minDist = shortestPath(16, distGraph, start, end);
	if (minDist == SIZE_MAX)
		printf("It seems that both nodes are disconnected from each other!\n");
	else
		printf("Minimum distance between node %zu and node %zu is: %zu\n", start, end, minDist);
	
	return EXIT_SUCCESS;
}
