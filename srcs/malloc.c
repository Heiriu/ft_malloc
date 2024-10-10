#include "../include/lib_malloc.h"

list_malloc s_malloc;

void	move_mem_up(int tab, int *tab_size, void **tab_ptr)
{
	if (tab_size[tab] > 0)
		move_mem_up(tab + 1, tab_size, tab_ptr);
	tab_size[tab + 1] = tab_size[tab];
	tab_ptr[tab + 1] = tab_ptr[tab];
}

void *allocate_struct(size_t size, int index, int count, int *nbr_alloc, int *tab_size, void **tab_ptr, void *ptr_zone)
{
	*nbr_alloc = *nbr_alloc + 1;
	tab_ptr[count] = ptr_zone + index;
	tab_size[count] = size;
	return (tab_ptr[count]);
}

int check_memory_between(int *index, int count, int size, int *tab_size, void **tab_ptr, void *ptr_zone)
{
	int i;

	i = 0;
	while (i < size)
	{
		if (ptr_zone + *index == tab_ptr[count])
		{
			*index = *index + tab_size[count];
			return (0);
		}
		*index = *index + 1;
		i++;
	}
	*index = *index - size;
	return (1);
}

void *alloc_tiny_small(size_t size, int *nbr_alloc, int *tab_size, void **tab_ptr, void *ptr_zone, int bloc_size)
{
	int index;
	int count;

	if (*nbr_alloc == 100)
	{
		write(2, "\033[0;31mERROR: cannot handle more allocation\n\033[0m", 49);
		return (NULL);
	}
	index = 0;
	count = 0;
	if (*nbr_alloc == 0)
		return (allocate_struct(size, index, 0, nbr_alloc, tab_size, tab_ptr, ptr_zone));
	while (index < bloc_size)
	{
		if (ptr_zone + index != tab_ptr[count], size)
		{
			if (check_memory_between(&index, count, size, tab_size, tab_ptr, ptr_zone) == 0)
				count++;
			else
			{
				move_mem_up(count, tab_size, tab_ptr);
				return (allocate_struct(size, index, count, nbr_alloc, tab_size, tab_ptr, ptr_zone));
			}
		}
		else
			index += tab_size[count++];
		if (count == *nbr_alloc)
			break;
	}
	return (allocate_struct(size, index, count, nbr_alloc, tab_size, tab_ptr, ptr_zone));
}

void *alloc_large(size_t size, int *nbr_alloc, int *tab_size, void **tab_ptr, void **ptr_zone)
{
	void *ptr;
	int count;

	ptr = NULL;
	if (*nbr_alloc == 100)
	{
		write(2, "\033[0;31mERROR: cannot handle more allocation\n\033[0m", 49);
		return (NULL);
	}
	if (*nbr_alloc == 0)
	{
		ptr = mmap(NULL, size, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, 0, 0);
		*ptr_zone = ptr;
		return (allocate_struct(size, 0, 0, nbr_alloc, tab_size, tab_ptr, ptr));
	}
	ptr = mmap(tab_ptr[0], size, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, 0, 0);
	count = *nbr_alloc;
	return (allocate_struct(size, 0, count, nbr_alloc, tab_size, tab_ptr, ptr));
}

void *ft_malloc(size_t size)
{
	if (size <= 0)
		return (NULL);
	if (s_malloc.pagesize == 0)
		init_malloc();
	if (size <= 100)
		return (alloc_tiny_small(size, &s_malloc.nbr_alloc_tiny, s_malloc.size_ptr_tiny, s_malloc.tab_ptr_tiny, s_malloc.ptr_zone_tiny, s_malloc.tiny_bloc_size));
	else if (size <= 4096)
		return (alloc_tiny_small(size, &s_malloc.nbr_alloc_small, s_malloc.size_ptr_small, s_malloc.tab_ptr_small, s_malloc.ptr_zone_small, s_malloc.small_bloc_size));
	return (alloc_large(size, &s_malloc.nbr_alloc_large, s_malloc.size_ptr_large, s_malloc.tab_ptr_large, &s_malloc.ptr_zone_large));
}