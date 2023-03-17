/* Created by: Nelson Cardona
 * Start Time/Date: 13:23/17-03-23
 * Completion Time/Date: 
 *
 * I'm going to assume that the graph is connected since we're using
 * SIZE_MAX to denote non-connections
 */
#include <stdlib.h>
#include <stdio.h>

#include <stdbool.h>
#include <stdint.h>

/* Get unvisited node w/ shortest distance */
size_t minDist(size_t nElem, size_t dist[nElem], bool visited[nElem]) {
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

	while (minDist(nElem, dist, visited) != end) {
		if (minDist(nElem, dist, visited) == SIZE_MAX)
			return SIZE_MAX;	// Every unvisited node is disconnected!!!
		size_t currNode = minDist(nElem, dist, visited);
		
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
	size_t distGraph[15][15];

	return EXIT_SUCCESS;
}
