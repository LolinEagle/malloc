#include "../inc/malloc.h"

extern t_zone	g_zone;

void*	realloc(void* ptr, size_t size){
	if (ptr == NULL){
		// realloc with a NULL pointer is equivalent to malloc
		return (malloc(size));
	}

	if (size == 0){
		// realloc with size 0 is equivalent to free
		free(ptr);
		return (NULL);
	}

	// Retrieve the block metadata associated with the given pointer
	t_block*	oldBlock = getBlockFromPtr(ptr);
	if (!oldBlock)
		return (NULL);// Invalid pointer

	// If the new size is less than or equal to the current block size, return (the same pointer
	if (size <= oldBlock->size)
		return (ptr);

	// Allocate a new block with the requested size
	void *new_ptr = malloc(size);
	if (!new_ptr)
		return (NULL);// Allocation failed

	// Copy data from the old block to the new block
	memcpy(new_ptr, ptr, oldBlock->size);// Copy only up to the old block's size

	// Free the old block
	free(ptr);

	return (new_ptr);
}
