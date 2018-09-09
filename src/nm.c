#include "../includes/nm.h"

void	nm(char *pr)
{

};

int	main(int ac, char **av)
{
	int		fd;
	char	*ptr;
	struct stat	buf;

	if (ac != 2)
		return print_usage();
	if ((fd = open(av[1], O_RDONLY)) < 0)
		return open_exit(av[1]);
	if (fstat(fd, &buf) < 0)
		return fstat_exit();
	if ((ptr = mmap(0, buf.st_size, PROT_READ, MAP_PRIVATE, fd, 0)) == MAP_FAILED)
		mmap_munmap_exit("mmap");
	nm(ptr);
	if (munmap(ptr, buf.st_size) < 0)
		mmap_munmap_exit("munmap");
	return 0;
};
