#include "../inc/malloc.h"

extern t_zone	g_zone;

void*	realloc(void* ptr, size_t size){
	if (ptr == NULL)
		return (malloc(size));
	if (size == 0){
		free(ptr);
		return (NULL);
	}

	// Retrieve the block metadata associated with the given pointer
	t_block*	oldBlock = getBlockFromPtr(ptr);
	if (!oldBlock)
		return (NULL);// Invalid pointer
	if (size <= oldBlock->size)
		return (ptr);

	// Allocate a new block with the requested size
	void *newPtr = malloc(size);
	if (!newPtr)
		return (NULL);// Allocation failed

	// Copy data from the old block to the new block
	memcpy(newPtr, ptr, oldBlock->size);// Copy only up to the old block's size
	free(ptr);// Free the old block
	return (newPtr);
}
