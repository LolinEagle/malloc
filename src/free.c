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
	t_block*	head;
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
		// If there is no next element or next id is not the same as "block" id
		if (!parent->next || parent->next->blockId != block->blockId)
			break ;
		// Iterator
		parent = parent->next;
	}

	// If only block in g_zone
	if (head != g_zone.large && !parent->next && lastChild == head){
		parent->size = (head == g_zone.tiny) ? TINYBLOCK : SMALLBLOCK;
		parent->freeSize = parent->size;
		parent->isFree = TRUE;
		parent->next = NULL;
		head = parent;
		pthread_mutex_unlock(&g_lock);
		return ;
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
		fprintf(stderr, "munmap() error : errno=%i\n", errno);
	pthread_mutex_unlock(&g_lock);
}
