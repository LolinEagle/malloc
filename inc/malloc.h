#pragma once

#include <string.h>
#include <sys/mman.h>
#include <unistd.h>

#define FALSE 0
#define TRUE 1
#define TINY 131072// 128KB
#define SMALL 1048576// 1MB
#define PAGE_SIZE sysconf(_SC_PAGESIZE)

typedef struct s_block{
	size_t			size;
	int				free;
	struct s_block*	next;
}	t_block;

typedef struct s_zone{
	t_block*	tiny;
	t_block*	small;
	t_block*	large;
}	t_zone;

t_block*	getBlockFromPtr(void *ptr);

void	free(void* ptr);
void*	malloc(size_t size);
void*	realloc(void* ptr, size_t size);
