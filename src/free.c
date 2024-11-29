#include "../inc/malloc.h"

extern t_zone	g_zone;

t_block*	getBlockFromPtr(void* ptr){
	if (!ptr)
		return (NULL);
	return ((t_block*)ptr - 1);// Go back to the start of the block metadata
}

void	freeBlock(t_block** head, void *ptr){
	t_block*	block = getBlockFromPtr(ptr);
	if (!block)
		return ;

	// Remove block from head
	t_block*	current = *head;
	while (current){
		if (current->next == block){
			current->next = block->next;
			break ;
		}
		current = current->next;
	}
	
	size_t	zoneSize;
	if (block->size <= 128) zoneSize = TINY;
	else if (block->size <= 1024) zoneSize = SMALL;
	else zoneSize = block->size + sizeof(t_block);

	if (munmap(block, zoneSize) < 0)
		fprintf(stderr, "munmap() error : errno=%i\n", errno);
}

void	free(void* ptr){
	if (!ptr)
		return ;

	t_block*	block = getBlockFromPtr(ptr);

	// Decide which zone the block belongs to and free it accordingly
	if (block->size <= 128)
		freeBlock(&g_zone.tiny, ptr);
	else if (block->size <= 1024)
		freeBlock(&g_zone.small, ptr);
	else
		freeBlock(&g_zone.large, ptr);
}
