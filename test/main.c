#include "../inc/malloc.h"

int	main(void){
	int		i;
	void*	ret[8];
	size_t	size[] = {
		1, 2, 3, 4, TINYBLOCK, TINYBLOCK + 1, SMALLBLOCK, SMALLBLOCK + 1
	};

	// Malloc
	for (i = 0; i < 8; i++)
		ret[i] = malloc(size[i]);
	show_alloc_mem();

	// Free
	for (i = 0; i < 8; i++)
		free(ret[i]);
	show_alloc_mem();

	return (0);
}
