/* Created by: Nelson Angelo Magno Cardona
 * Start Time/Date: 15:18/6-03-23
 * Completion Time/Date: 
 */
#include <stdlib.h>
#include <stdio.h>

/* For SIZE_MAX */
#include <stdint.h>

/* Initialization of index table */
void init(size_t parent[], size_t parent_size) {
		/* Set all elements as singletons */
		for (size_t i = 0; i < parent_size; ++i)
				parent[i] = SIZE_MAX;
}

size_t Find(size_t parent[], size_t element) {
		if (parent[element] != SIZE_MAX)
				return Find(parent, parent[element]);
		return element;
}

size_t FindReplace(size_t parent[], size_t element, size_t new_parent) {
		size_t old_parent = parent[element];
		parent[element] = new_parent;
		if (old_parent != SIZE_MAX) {
				return FindReplace(parent, old_parent, new_parent);
		}
		return element;
}

size_t FindCompress(size_t parent[], size_t element) {
		if (parent[element] != SIZE_MAX) {
				parent[element] = FindCompress(parent, parent[element]);
				return parent[element];
		}
		return element;
}

void Union(size_t parent[], size_t parent_tree, size_t child_tree) {
		if (Find(parent, parent_tree) == Find(parent, child_tree)) {
				printf("Invalid union: Both elements are in the same set.\n");
				return;
		}

		FindReplace(parent, child_tree, FindCompress(parent, parent_tree));
}

int main(int argc, char* argv[argc+1]) {
#ifdef NOTHING
		/* Check there is at least one argument */
		size_t parent_size = atoi(argv[1]);
		/* Check that parent_size > 0 */
		if (!parent_size) {
				printf("Sorry, an array cannot be size 0. Exiting...\n")
						return EXIT_FAILURE;
		}
		size_t parent[parent_size] = {0}; // Remember: IGNORE THIS WARNING.
		
		init(parent, parent_size);
#endif
#define parent_size 20
		size_t parent[parent_size] = {9, SIZE_MAX, 10, SIZE_MAX, 9, 3, 5, 0, 5, SIZE_MAX, 9, 1, 3, 4, 5, 2, 11, 4, 1, 4};

		printf("The root of each element is:\n");
		for (size_t i = 0; i < parent_size; ++i) {
				printf("p[%ld]: %ld", i, Find(parent, i));
				if (i < parent_size)
						printf(", ");
		}
		printf("\n");

		FindReplace(parent, 16, 69);
		FindReplace(parent, 6, 420);
		FindReplace(parent, 2, 21);

		printf("PSYCH!!! The new index table is:\n");
		for (size_t i = 0; i < parent_size; ++i) {
				printf("p[%ld]: %ld", i, parent[i]);
				if (i < parent_size)
						printf(", ");
		}
		printf("\n");


		return EXIT_SUCCESS;
}
