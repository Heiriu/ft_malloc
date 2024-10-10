#include "../include/lib_malloc.h"

int display_memory(char *type, void *ptr, void **tab, int *tab_size, int nbr_alloc)
{
	int index;
	int count;
	int bytes;

	index = 0;
	count = 0;
	bytes = 0;
	printf("%s : %p\n", type, ptr);
	while (count < nbr_alloc && count < 100)
	{
		if (tab[index] != NULL)
		{
			printf("%i| %p - %p : %i\n",index, tab[index], ((tab[index] + tab_size[index]) - 1), tab_size[index]);
			count++;
			bytes += tab_size[index];
		}
		index++;
	}
	return (bytes);
}

void show_alloc_mem()
{
	int bytes;

	bytes = 0;

	bytes = display_memory("TINY", s_malloc.ptr_zone_tiny, s_malloc.tab_ptr_tiny, s_malloc.size_ptr_tiny, s_malloc.nbr_alloc_tiny);
	bytes += display_memory("SMALL", s_malloc.ptr_zone_small, s_malloc.tab_ptr_small, s_malloc.size_ptr_small, s_malloc.nbr_alloc_small);
	bytes += display_memory("LARGE", s_malloc.ptr_zone_large, s_malloc.tab_ptr_large, s_malloc.size_ptr_large, s_malloc.nbr_alloc_large);
	printf("Total : %i bytes\n\n", bytes);
}