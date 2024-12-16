#include "../inc/malloc.h"

t_zone	g_zone = {NULL, NULL, NULL};// Global zone to manage allocations

void*	splitBlock(t_block** current, size_t size, t_block** head){
	t_block*	oldBlock = *current;
	t_block*	newBlock = (void*)oldBlock + sizeof(t_block) + notFree(oldBlock);
	size_t		newFreeSize = oldBlock->freeSize - sizeof(t_block) - size;

	newBlock->size = size + newFreeSize;
	newBlock->freeSize = newFreeSize;
	newBlock->next = oldBlock;
	oldBlock->size = oldBlock->size - oldBlock->freeSize;
	oldBlock->freeSize = 0;
	*head = newBlock;
	return ((void*)(newBlock + 1));
}

void*	findFreeBlock(t_block** head, size_t size){
	t_block*	current = *head;
	while (current){
		if (current->freeSize > size + sizeof(t_block))
			return (splitBlock(&current, size, head));
		current = current->next;
	}

	// Size of block to allocat
	size_t		zoneSize;
	if (size <= TINYBLOCK) zoneSize = TINY;
	else if (size <= SMALLBLOCK) zoneSize = SMALL;
	else zoneSize = sizeof(t_block) + size;

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
	else if (size <= TINYBLOCK)
		return (findFreeBlock(&g_zone.tiny, size));
	else if (size <= SMALLBLOCK)
		return (findFreeBlock(&g_zone.small, size));
	else
		return (findFreeBlock(&g_zone.large, size));
}
