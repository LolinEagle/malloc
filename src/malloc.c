#include "../inc/malloc.h"

t_zone	g_zone = {NULL, NULL, NULL};// Global zone to manage allocations

// TO DO merge with findFreeBlock()
void*	initializeBlock(size_t size){
	void*	ptr = mmap(NULL, size, PROT, FLAGS, -1, 0);
	if (ptr == MAP_FAILED)
		return (NULL);
	t_block*	block = (t_block*)ptr;
	block->size = size - sizeof(t_block);
	block->free = FALSE;
	block->next = NULL;
	return ((void*)(block + 1));
}

void*	findFreeBlock(t_block** head, size_t size){
	t_block*	current = *head;// Recover the head of the linked list
	while (current){
		if (current->free && current->size >= size){
			current->free = FALSE;
			return ((void*)(current + 1));
		}
		current = current->next;
	}

	size_t		zoneSize = (size <= 128) ? TINY : SMALL;
	t_block*	newBlock = (t_block*)mmap(NULL, zoneSize, PROT, FLAGS, -1, 0);
	if (newBlock == MAP_FAILED)
		return (NULL);
	newBlock->size = zoneSize - sizeof(t_block);
	newBlock->free = FALSE;
	newBlock->next = *head;
	*head = newBlock;
	return ((void*)(newBlock + 1));// Return the address after block metadata
}

void*	malloc(size_t size){
	write(1, "ft_malloc is called\n", 21);
	if (size <= 128)
		return (findFreeBlock(&g_zone.tiny, size));
	else if (size <= 1024)
		return (findFreeBlock(&g_zone.small, size));
	else
		return (initializeBlock(size + sizeof(t_block)));
}
