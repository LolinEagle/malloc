#pragma once

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/mman.h>
#include <unistd.h>

#define PAGESIZE (size_t)sysconf(_SC_PAGESIZE)
#define TINY (PAGESIZE * 32)
#define SMALL (PAGESIZE * 256)
#define PROT PROT_READ | PROT_WRITE
#define FLAGS MAP_ANONYMOUS | MAP_PRIVATE

typedef struct s_block{
	size_t			size;
	struct s_block*	next;
}	t_block;

typedef struct s_zone{
	t_block*	tiny;
	t_block*	small;
	t_block*	large;
}	t_zone;

t_block*	getBlockFromPtr(void* ptr);
void		showAllocMem(void);

void		free(void* ptr);
void*		malloc(size_t size);
void*		realloc(void* ptr, size_t size);
