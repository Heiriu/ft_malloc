#include "../include/lib_malloc.h"

int search_ptr(void *ptr)
{
	int i;

	i = 0;
	while (i < 100)
	{		
		if (ptr == s_malloc.tab_ptr_tiny[i])
			return (i);
		else if (ptr == s_malloc.tab_ptr_small[i])
			return (i + 100);
		else if (ptr == s_malloc.tab_ptr_large[i])
			return (i + 200);
		i++;
	}
	return (300);
}

void *cpy_lenght_ptr(size_t size, void *ptr, int tab_size)
{
	void *new_ptr;
	int i;

	new_ptr = ft_malloc(size);
	char *ptr1 = new_ptr;
	char *ptr2 = ptr;
	i = 0;
	while (i < size && i < tab_size)
	{
		ptr1[i] = ptr2[i];
		i++;
	}
	ft_free(ptr);
	return (new_ptr);
}

void *realloc_tiny(size_t size, int i, void *ptr)
{
	if (i != size)
		return (cpy_lenght_ptr(size, s_malloc.tab_ptr_tiny[i], s_malloc.size_ptr_tiny[i]));
	return (ptr);
}

void *realloc_small(size_t size, int i, void *ptr)
{
	if (i != size)
		return (cpy_lenght_ptr(size, s_malloc.tab_ptr_small[i], s_malloc.size_ptr_small[i]));
	return (ptr);
}

void *realloc_large(size_t size, int i, void *ptr)
{
	if (i != size)
		return (cpy_lenght_ptr(size, s_malloc.tab_ptr_large[i], s_malloc.size_ptr_large[i]));
	return (ptr);
}

void *ft_realloc(void *ptr, size_t size)
{
	int i;

	i = 0;
	if (ptr == NULL && size > 0)
		return (ft_malloc(size));
	else if (ptr != NULL && size == 0)
	{
		ft_free(ptr);
		return (NULL);
	}

	i = search_ptr(ptr);
	if (i < 100)
		return (realloc_tiny(size, i, ptr));
	else if (i < 200)
		return (realloc_small(size, (i - 100), ptr));
	else if (i < 300)
		return (realloc_large(size, (i - 200), ptr));
	write(2, "\033[0;31mERROR: cannot realloc\n\033[0m", 34);
	return (NULL);
}