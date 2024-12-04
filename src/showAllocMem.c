#include "../inc/malloc.h"

extern t_zone	g_zone;

size_t	notFree(t_block* b){
	return (b->size - b->freeSize);
}

void	printAllocMem(t_block** head, size_t* total){
	for (t_block* b = *head; b; b = b->next){
		fprintf(stderr, "%p - %p : %zu bytes\n", b, b + b->size, notFree(b));
		*total += b->size;
	}
}

void		showAllocMem(void){
	size_t	total = 0;

	if (g_zone.tiny){
		fprintf(stderr, "TINY : %p\n", g_zone.tiny);
		printAllocMem(&g_zone.tiny, &total);
	}
	if (g_zone.small){
		fprintf(stderr, "SMALL : %p\n", g_zone.small);
		printAllocMem(&g_zone.small, &total);
	}
	if (g_zone.large){
		fprintf(stderr, "LARGE : %p\n", g_zone.large);
		printAllocMem(&g_zone.large, &total);
	}
	fprintf(stderr, "Total : %zu bytes allocated\n\n", total);
}
