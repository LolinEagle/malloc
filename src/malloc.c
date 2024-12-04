#include "../inc/malloc.h"

t_zone	g_zone = {NULL, NULL, NULL};// Global zone to manage allocations

void*	findFreeBlock(t_block** head, size_t size){
	// Size of block to allocat
	size_t		zoneSize = sizeof(t_block);
	if (size <= TINY) zoneSize += TINY;
	else if (size <= SMALL) zoneSize += SMALL;
	else zoneSize += size;

	// Call mmap to allocat memory
	t_block*	newBlock = (t_block*)mmap(NULL, zoneSize, PROT, FLAGS, -1, 0);
	if (newBlock == MAP_FAILED)
		return (NULL);
	newBlock->size = zoneSize - sizeof(t_block);
	newBlock->freeSize = newBlock->size - size;
	newBlock->next = *head;

	// Make the new block the head of the linked list and return
	*head = newBlock;
	return ((void*)(newBlock + 1));// Return the address after block metadata
}

void*	malloc(size_t size){
	if (size <= 0)
		return (NULL);
	else if (size <= TINY)
		return (findFreeBlock(&g_zone.tiny, size));
	else if (size <= SMALL)
		return (findFreeBlock(&g_zone.small, size));
	else
		return (findFreeBlock(&g_zone.large, size));
}
