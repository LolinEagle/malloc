#include "../inc/malloc.h"

extern t_zone	g_zone;

void		showAllocMem(void){
	size_t	total = 0;

	printf("TINY :\n");
	for (t_block* b = g_zone.tiny; b; b = b->next){
		printf("%p - %p : %zu bytes\n", b, (void*)b + b->size, b->size);
		total += b->size;
	}

	printf("SMALL :\n");
	for (t_block* b = g_zone.small; b; b = b->next){
		printf("%p - %p : %zu bytes\n", b, (void*)b + b->size, b->size);
		total += b->size;
	}

	printf("LARGE :\n");
	for (t_block* b = g_zone.large; b; b = b->next){
		printf("%p - %p : %zu bytes\n", b, (void*)b + b->size, b->size);
		total += b->size;
	}

	printf("Total: %zu bytes allocated\n", total);
}
