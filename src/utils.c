#include "../inc/malloc.h"

void*		memcpy(void* dest, const void* src, size_t n){
	char*		d = (char*)dest;
	const char*	s = (char*)src;

	while (n--)
		*d++ = *s++;
	return (dest);
}

t_block*	getBlock(void* ptr){
	if (!ptr)
		return (NULL);
	return ((t_block*)ptr - 1);// Go back to the start of the block metadata
}

void*		getPtr(t_block* block){
	if (!block)
		return (NULL);
	return ((void*)block + sizeof(t_block));
}

size_t		notFree(t_block* b){
	return (b->size - b->freeSize);
}

void		printBlock(t_block* b){
	if (!b){
		fprintf(stderr, "block is NULL\n");
		return ;
	}
	fprintf(stderr,
		"block=%p size=%li freeSize=%li isFree=%i blockId=%i next=%p\n",
		b, b->size, b->freeSize, b->isFree, b->blockId, b->next
	);
}

void		printAllocMem(t_block** head, size_t* total){
	for (t_block* b = *head; b; b = b->next){
		fprintf(stderr, "%p - %p : %li/%li bytes\n",
			getPtr(b), getPtr(b) + b->size, notFree(b), b->size);
		*total += b->size + sizeof(t_block);
	}
}

void		show_alloc_mem(void){
	pthread_mutex_lock(&g_lock);
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
	pthread_mutex_unlock(&g_lock);
}
