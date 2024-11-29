#include "../inc/malloc.h"

extern t_zone	g_zone;

void		showAllocMem(void){
	size_t	total = 0;

	if (g_zone.tiny) fprintf(stderr, "TINY :\n");
	for (t_block* b = g_zone.tiny; b; b = b->next){
		fprintf(stderr, "%p - %p : %zu bytes\n", b, (void*)b + b->size, b->size);
		total += b->size;
	}

	if (g_zone.small) fprintf(stderr, "SMALL :\n");
	for (t_block* b = g_zone.small; b; b = b->next){
		fprintf(stderr, "%p - %p : %zu bytes\n", b, (void*)b + b->size, b->size);
		total += b->size;
	}

	if (g_zone.large) fprintf(stderr, "LARGE :\n");
	for (t_block* b = g_zone.large; b; b = b->next){
		fprintf(stderr, "%p - %p : %zu bytes\n", b, (void*)b + b->size, b->size);
		total += b->size;
	}

	fprintf(stderr, "Total : %zu bytes allocated\n", total);
}
