#include "../inc/malloc.h"

t_zone	g_zone = {NULL, NULL, NULL};// Global zone to manage allocations

void*	findFreeBlock(t_block** head, size_t size){
	size_t		zoneSize;
	if (size <= TINY) zoneSize = TINY;
	else if (size <= SMALL) zoneSize = SMALL;
	else zoneSize = size + sizeof(t_block);

	t_block*	newBlock = (t_block*)mmap(NULL, zoneSize, PROT, FLAGS, -1, 0);
	if (newBlock == MAP_FAILED)
		return (NULL);
	newBlock->size = zoneSize - sizeof(t_block);
	newBlock->next = *head;

	*head = newBlock;
	return ((void*)(newBlock + 1));// Return the address after block metadata
}

void*	malloc(size_t size){
	if (size == 0)
		return (NULL);
	else if (size <= TINY)
		return (findFreeBlock(&g_zone.tiny, size));
	else if (size <= SMALL)
		return (findFreeBlock(&g_zone.small, size));
	else
		return (findFreeBlock(&g_zone.large, size));
}
