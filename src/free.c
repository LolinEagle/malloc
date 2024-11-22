#include "../inc/malloc.h"

extern t_zone	g_zone;

t_block*	getBlockFromPtr(void *ptr){
	if (!ptr)
		return (NULL);
	return ((t_block*)ptr - 1);// Go back to the start of the block metadata
}

void	freeBlock(t_block** head, void *ptr){
	(void)head;
	t_block*	block = getBlockFromPtr(ptr);
	if (!block)
		return ;
	block->free = TRUE;// Mark the block as free
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
		munmap(block, block->size + sizeof(t_block));
}
