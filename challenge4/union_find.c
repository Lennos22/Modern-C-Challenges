/* Created by: Nelson Angelo Magno Cardona
 * Start Time/Date: 15:18/6-03-23
 * Completion Time/Date: 
 */
#include <stdlib.h>
#include <stdio.h>

/* Initialization of index table */
void init(size_t parent[], size_t parent_size) {
		/* Set all elements as singletons */
		for (size_t i = 0; i < parent_size; ++i)
				parent[i] = SIZE_MAX;
}

size_t Find(size_t parent[], size_t element) {
		if (parent[element] != SIZE_MAX)
				return find(parent, parent[element]);
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

		size_t parent[12] = {9, SIZE_MAX, 3, SIZE_MAX, 1, 3, 5, 5, 5, SIZE_MAX, 9, 9};

		printf("The roots of each element are:\n");
		for (size_t i = 0; i < 12; ++i) {
				printf("p[%ld]: %ld", i, Find(parent, i));
				if (i == 11)
						printf(", ");
		}
		printf("\n");


		return EXIT_SUCCESS;
}
