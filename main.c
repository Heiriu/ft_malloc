#include "include/lib_malloc.h"

int main()
{
	char *str;
	int i = 0;

	str = ft_malloc(500);
	while (i < 500)
		str[i++] = 'a';
	printf("%s\n", str);
	show_alloc_mem();
	str = ft_realloc(str, 40);
	show_alloc_mem();
	printf("%s\n", str);
	str = ft_realloc(str, 40000);
	printf("%p\n", str);
	show_alloc_mem();
	return (0);
}