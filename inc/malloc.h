#pragma once

#include <errno.h>
#include <pthread.h>
#include <stdio.h>
#include <sys/mman.h>
#include <unistd.h>

#define FALSE 0
#define TRUE 1
#define PAGESIZE (size_t)sysconf(_SC_PAGESIZE)
#define TINY PAGESIZE * 8
#define SMALL PAGESIZE * 16
#define TINYBLOCK TINY - sizeof(t_block)
#define SMALLBLOCK SMALL - sizeof(t_block)
#define PROT PROT_READ | PROT_WRITE
#define FLAGS MAP_ANONYMOUS | MAP_PRIVATE

typedef struct s_block{
	size_t			size;
	size_t			freeSize;
	int				isFree;
	__uint16_t		blockId;
	struct s_block*	next;
}	t_block;

typedef struct s_zone{
	t_block*	tiny;
	t_block*	small;
	t_block*	large;
}	t_zone;

extern t_zone			g_zone;
extern pthread_mutex_t	g_lock;

// Utils
void*		memcpy(void* dest, const void* src, size_t n);
t_block*	getBlock(void* ptr);
size_t		notFree(t_block* b);
void		show_alloc_mem(void);

void		free(void* ptr);
void*		malloc(size_t size);
void*		realloc(void* ptr, size_t size);
