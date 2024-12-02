#include "../inc/malloc.h"

int	main(void){
	// Malloc
	char*	one = malloc(1);
	if (!one)
		return (1);
	char*	two = malloc(TINY);
	if (!two)
		return (1);
	char*	tri = malloc(SMALL);
	if (!tri)
		return (1);

	// Realloc

	// Free
	showAllocMem();
	free(one);
	showAllocMem();
	free(two);
	free(tri);
	showAllocMem();
	return (0);
}
