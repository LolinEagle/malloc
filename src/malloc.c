#include "../inc/malloc.h"

t_zone	g_zone = {NULL, NULL, NULL};// Global zone to manage allocations

void*	initializeBlock(size_t size){
	void*	ptr = mmap(NULL, size, PROT_READ | PROT_WRITE, MAP_PRIVATE, -1, 0);

	if (ptr == MAP_FAILED)
		return (NULL);
	t_block*	block = (t_block *)ptr;
	block->size = size - sizeof(t_block);
	block->free = FALSE;
	block->next = NULL;
	return ((void *)(block + 1));// return the address after block metadata
}

void*	findFreeBlock(t_block** head, size_t size){
	t_block*	current = *head;
	while (current){
		if (current->free && current->size >= size){
			current->free = FALSE;
			return ((void *)(current + 1));
		}
		current = current->next;
	}

	size_t		zone_size = (size <= 128) ? TINY : SMALL;
	t_block*	new_block = (t_block*)mmap(NULL, zone_size, PROT_READ | PROT_WRITE, MAP_PRIVATE, -1, 0);

	if (new_block == MAP_FAILED)
		return (NULL);
	new_block->size = zone_size - sizeof(t_block);
	new_block->free = FALSE;
	new_block->next = *head;
	*head = new_block;
	return ((void*)(new_block + 1));
}

void*	malloc(size_t size){
    write(1, "C'est le custom malloc qui est appelé\n", 40);
	if (size <= 128)
		return (findFreeBlock(&g_zone.tiny, size));
	else if (size <= 1024)
		return (findFreeBlock(&g_zone.small, size));
	else
		return (initializeBlock(size + sizeof(t_block)));
}
