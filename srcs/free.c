#include "../include/lib_malloc.h"

void	move_mem(int tab, int *tab_size, void **tab_ptr)
{
	if (tab_size[tab + 1] != 0)
	{
		tab_size[tab] = 0;
		tab_ptr[tab] = NULL;
		tab_size[tab] = tab_size[tab + 1];
		tab_ptr[tab] = tab_ptr[tab + 1];
		move_mem(tab + 1, tab_size, tab_ptr);
	}
}

void empty_malloc()
{
	int i;

	i = 0;
	while (i < 100)
	{
		s_malloc.size_ptr_tiny[i] = 0;
		s_malloc.size_ptr_small[i] = 0;
		s_malloc.size_ptr_large[i] = 0;

		s_malloc.tab_ptr_tiny[i] = NULL;
		s_malloc.tab_ptr_small[i] = NULL;	
		s_malloc.tab_ptr_large[i++] = NULL;
	}

	s_malloc.nbr_alloc_tiny = 0;
	s_malloc.nbr_alloc_small = 0;
	s_malloc.nbr_alloc_large = 0;

	if (munmap(s_malloc.ptr_zone_tiny, s_malloc.tiny_bloc_size) != 0)
	{
		write(2, "\033[0;31mERROR: cannot free\n\033[0m", 31);
		return;
	}
	else if (munmap(s_malloc.ptr_zone_small, s_malloc.small_bloc_size) != 0)
	{
		write(2, "\033[0;31mERROR: cannotT free\n\033[0m", 31);
		return;
	}

	s_malloc.pagesize = 0;
	s_malloc.tiny_bloc_size = 0;
	s_malloc.small_bloc_size = 0;

	s_malloc.ptr_zone_tiny = NULL;
	s_malloc.ptr_zone_small = NULL;
	s_malloc.ptr_zone_large = NULL;
}

void ft_free(void *ptr)
{
	int index;

	if (ptr == NULL)
		return;
	
	index = 0;
	while (index < 100)
	{
		if (ptr == s_malloc.tab_ptr_tiny[index])
		{
			s_malloc.nbr_alloc_tiny--;
			s_malloc.tab_ptr_tiny[index] = NULL;
			s_malloc.size_ptr_tiny[index] = 0;
			if (s_malloc.nbr_alloc_tiny == 0 && s_malloc.nbr_alloc_small == 0 && s_malloc.nbr_alloc_large == 0)
			{
				empty_malloc();
				return;
			}
			move_mem(index, s_malloc.size_ptr_tiny, s_malloc.tab_ptr_tiny);
			return;
		}
		index++;
	}
	
	index = 0;
	while (index < 100)
	{
		if (ptr == s_malloc.tab_ptr_small[index])
		{
			s_malloc.nbr_alloc_small--;
			s_malloc.tab_ptr_small[index] = NULL;
			s_malloc.size_ptr_small[index] = 0;
			if (s_malloc.nbr_alloc_tiny == 0 && s_malloc.nbr_alloc_small == 0 && s_malloc.nbr_alloc_large == 0)
			{
				empty_malloc();
				return;
			}
			move_mem(index, s_malloc.size_ptr_small, s_malloc.tab_ptr_small);
			return;
		}
		index++;
	}
	
	index = 0;
	while (index < 100)
	{
		if (ptr == s_malloc.tab_ptr_large[index])
		{
			if (munmap(s_malloc.tab_ptr_large[index], s_malloc.size_ptr_large[index]) != 0)
			{
				write(2, "\033[0;31mERROR: cannot free\n\033[0m", 31);
				return;
			}
			s_malloc.nbr_alloc_large--;
			s_malloc.tab_ptr_large[index] = NULL;
			s_malloc.size_ptr_large[index] = 0;
			if (s_malloc.nbr_alloc_tiny == 0 && s_malloc.nbr_alloc_small == 0 && s_malloc.nbr_alloc_large == 0)
			{
				empty_malloc();
				return;
			}
			move_mem(index, s_malloc.size_ptr_large, s_malloc.tab_ptr_large);
			return;
		}
		index++;
	}
	write(2, "\033[0;31mERROR: double free\n\033[0m", 31);
	return;
}