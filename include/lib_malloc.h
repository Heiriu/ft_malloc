#ifndef LIB_MALLOC_H
#define LIB_MALLOC_H

#include <stdio.h>
#include <unistd.h>
#include <sys/mman.h>
#include <sys/resource.h>
#include <string.h>
#include <assert.h>
#include <ctype.h>
#include <pthread.h>
#include <stdlib.h>

typedef struct structure_list_malloc
{

	int pagesize;
	int tiny_bloc_size;			// 1 to 100 bytes  espace: 12288
	int small_bloc_size;		// 101 to 4000 bytes espace : 413696

	void *ptr_zone_tiny;		//address debut de la page
	void *ptr_zone_small;
	void *ptr_zone_large;

	int nbr_alloc_tiny;			//data tiny zone
	int size_ptr_tiny[100];
	void *tab_ptr_tiny[100];

	int nbr_alloc_small;		//data small zone
	int size_ptr_small[100];
	void *tab_ptr_small[100];

	int nbr_alloc_large;		//data large zone
	int size_ptr_large[100];
	void *tab_ptr_large[100];

} list_malloc;

extern list_malloc s_malloc;

void ft_free(void *ptr);
void *ft_malloc(size_t size);
void *ft_realloc(void *ptr, size_t size);

void show_alloc_mem();

void init_malloc();

#endif