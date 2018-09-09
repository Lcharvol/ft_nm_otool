#include "../includes/nm.h"

int	print_usage(void)
{
	ft_printf("Please give me an arg\n");
	return (EXIT_FAILURE);
};

int open_exit(char *file_name)
{
    ft_printf("Fail to open '%s' file\n", file_name);
	return (EXIT_FAILURE);
};

int fstat_exit(void)
{
    ft_printf("fstat: error\n");
	return (EXIT_FAILURE);
}

int mmap_munmap_exit(char *type)
{
    ft_printf("%s: error\n", type);
	return (EXIT_FAILURE);
}