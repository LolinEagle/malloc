#include "../inc/malloc.h"

extern t_zone	g_zone;

t_block*	getBlockFromPtr(void* ptr){
	if (!ptr)
		return (NULL);
	return ((t_block*)ptr - 1);// Go back to the start of the block metadata
}

void	free(void* ptr){
	// Get block to free
	t_block*	block = getBlockFromPtr(ptr);
	if (!block)
		return ;

	// Decide which zone the block belongs to
	t_block*	current;
	size_t		zoneSize;
	if (block->size <= TINY){
		current = g_zone.tiny;
		zoneSize = TINY;
	} else if (block->size <= SMALL){
		current = g_zone.small;
		zoneSize = SMALL;
	} else {
		current = g_zone.large;
		zoneSize = block->size + sizeof(t_block);
	}

	// Remove block from g_zone
	if (block == current){
		// If first block of g_zone
		if (block->size <= TINY)
			g_zone.tiny = (block->next) ? block->next : NULL;
		else if (block->size <= SMALL)
			g_zone.small = (block->next) ? block->next : NULL;
		else
			g_zone.large = (block->next) ? block->next : NULL;
	} else {
		while (current){
			if (current->next == block){
				current->next = block->next;
				break ;
			}
			current = current->next;
		}
	}

	// Free
	if (munmap(block, zoneSize) < 0)
		fprintf(stderr, "munmap() error : errno=%i\n", errno);
}
