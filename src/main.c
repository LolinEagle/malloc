#include "../inc/malloc.h"

int	main(void){
	int		i;
	void*	ret[8];
	size_t	size[] = {1, 2, 3, 4, TINY, TINY + 1, SMALL, SMALL + 1};

	// Malloc
	for (i = 0; i < 8; i++)
		ret[i] = malloc(size[i]);
	show_alloc_mem();

	// Realloc
	for (i = 0; i < 5; i++)
		ret[i] = realloc(ret[i], size[i] + TINY);
	show_alloc_mem();

	// Free
	for (i = 0; i < 8; i++)
		free(ret[i]);
	show_alloc_mem();

	return (0);
}
