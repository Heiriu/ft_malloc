#include "../include/lib_malloc.h"

void	init_malloc()
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

	s_malloc.pagesize = getpagesize();
	s_malloc.tiny_bloc_size = s_malloc.pagesize * 3;
	s_malloc.small_bloc_size = s_malloc.pagesize * 101;

	s_malloc.nbr_alloc_tiny = 0;
	s_malloc.nbr_alloc_small = 0;
	s_malloc.nbr_alloc_large = 0;

	s_malloc.ptr_zone_large = NULL;
	s_malloc.ptr_zone_small = mmap(NULL, s_malloc.small_bloc_size, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, 0, 0);
	s_malloc.ptr_zone_tiny = mmap(NULL, s_malloc.tiny_bloc_size, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, 0, 0);
	if (s_malloc.ptr_zone_tiny == NULL || s_malloc.ptr_zone_small == NULL)
	{
		write(2, "\033[0;31mERROR: cannot allocate memory bloc\n\033[0m", 47);
		exit(-1);
	}
	//printf("%i\n%i\n%i\n", s_malloc.pagesize, s_malloc.tiny_bloc_size, s_malloc.small_bloc_size);
	//printf("%p\n%p\n", s_malloc.ptr_zone_tiny, s_malloc.ptr_zone_small);
}