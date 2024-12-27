#include "../inc/malloc.h"

void	free(void* ptr){
	pthread_mutex_lock(&g_lock);

	// Get block to free
	t_block*	block = getBlock(ptr);
	if (!block){
		pthread_mutex_unlock(&g_lock);
		return ;
	}

	// Change metadata
	block->isFree = TRUE;

	// Decide which zone the block belongs to
	/*t_block*	head;
	size_t		zoneSize;
	if (block->size <= TINYBLOCK){
		head = g_zone.tiny;
		zoneSize = TINY;
	} else if (block->size <= SMALLBLOCK){
		head = g_zone.small;
		zoneSize = SMALL;
	} else {
		head = g_zone.large;
		zoneSize = block->size + sizeof(t_block);
	}

	// Recover the parent block and check if all sub block is free
	t_block*	parent = head;
	while (parent->blockId != block->blockId)
		parent = parent->next;
	t_block*	lastChild = parent;
	while (parent->blockId == block->blockId){
		if (parent->isFree == FALSE){
			pthread_mutex_unlock(&g_lock);
			return ;
		}
		if (!parent->next || parent->next->blockId != block->blockId)
			break ;
		parent = parent->next;
	}

	// Remove block from g_zone
	if (lastChild == head){
		// If first block of g_zone
		if (block->size <= TINYBLOCK)
			g_zone.tiny = parent->next;
		else if (block->size <= SMALLBLOCK)
			g_zone.small = parent->next;
		else
			g_zone.large = parent->next;
	} else {
		while (head){
			if (head->next == lastChild){
				head->next = parent->next;
				break ;
			}
			head = head->next;
		}
	}

	// Free
	if (munmap(parent, zoneSize) < 0)
		fprintf(stderr, "munmap() error : errno=%i\n", errno);*/
	pthread_mutex_unlock(&g_lock);
}
