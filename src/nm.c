#include "../includes/nm.h"

void						print_output(int nsyms, int symoff, int stroff, char *ptr)
{
	int						i;
	char					*stringtable;
	struct nlist_64			*array;

	i = 0;
	array = (void *)ptr + symoff;
	stringtable = (void *)ptr + stroff;
	while(i < nsyms)
	{
		ft_printf("%s\n", stringtable + array[i].n_un.n_strx);
		i++;
	}
}

void						handle_64(char *ptr)
{
	int						ncmds;
	int						i;
	struct mach_header_64	*header;
	struct load_command		*lc;
	struct symtab_command	*sym;

	i = 0;
	header = (struct mach_header_64 *)ptr;
	ncmds = header->ncmds;
	lc = (void *)ptr + sizeof(*header);
	while(i < ncmds)
	{
		if(lc->cmd == LC_SYMTAB)
		{
			sym = (struct symtab_command *)lc;
			print_output(sym->nsyms, sym->symoff, sym->stroff, ptr);
			break ;
		};
		lc = (void *)lc + lc->cmdsize;
		i++;
	}
}

void						nm(char *ptr)
{
	unsigned int						magic_number;

	magic_number = *(int *) ptr;
	if(magic_number == MH_MAGIC_64)
		handle_64(ptr);
}

int							main(int ac, char **av)
{
	int						fd;
	char					*ptr;
	struct stat				buf;

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
