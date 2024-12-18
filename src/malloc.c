#include "../inc/malloc.h"

t_zone	g_zone = {NULL, NULL, NULL};// Global zone to manage allocations

void*	reallocBlock(t_block** current, size_t size){
	t_block*	new = *current;

	new->freeSize = new->size - size;
	new->isFree = FALSE;
	return ((void*)(new + 1));
}

void*	splitBlock(t_block** current, size_t size, t_block** head){
	t_block*	old = *current;
	t_block*	new = (void*)old + sizeof(t_block) + notFree(old);
	size_t		newFreeSize = old->freeSize - sizeof(t_block) - size;

	new->size = size + newFreeSize;
	new->freeSize = newFreeSize;
	new->isFree = FALSE;
	new->blockId = old->blockId;
	new->next = old;

	old->size = old->size - old->freeSize;
	old->freeSize = 0;
	*head = new;
	return ((void*)(new + 1));
}

void*	findFreeBlock(t_block** head, size_t size){
	t_block*	current = *head;
	while (current){
		if (current->isFree && current->size >= size + sizeof(t_block))
			return (reallocBlock(&current, size));
		if (current->freeSize >= size + sizeof(t_block))
			return (splitBlock(&current, size, head));
		current = current->next;
	}

	// Size of block to allocat
	size_t	zoneSize;
	if (size <= TINYBLOCK) zoneSize = TINY;
	else if (size <= SMALLBLOCK) zoneSize = SMALL;
	else zoneSize = sizeof(t_block) + size;

	static __uint16_t	id = 0;

	// Call mmap to allocat memory
	t_block*	new = (t_block*)mmap(NULL, zoneSize, PROT, FLAGS, -1, 0);
	if (new == MAP_FAILED)
		return (NULL);
	new->size = zoneSize - sizeof(t_block);
	new->freeSize = new->size - size;
	new->isFree = FALSE;
	new->blockId = id++;
	new->next = *head;

	// Make the new block the head of the linked list and return
	*head = new;
	return ((void*)(new + 1));// Return the address after block metadata
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
