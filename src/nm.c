#include "../includes/nm.h"

unsigned char				get_type(unsigned char ptr)
{
	
	// ft_printf("type: %d\n", ptr);
	if(ptr == 191)
		return 'U';
	return ' ';
};

void						print_output(int nsyms, int symoff, int stroff, char *ptr)
{
	int						i;
	char					*stringtable;
	struct nlist_64			*array;
	unsigned long			value;
	unsigned char			type;

	i = 0;
	array = (void *)ptr + symoff;
	stringtable = (void *)ptr + stroff;
	while(i < nsyms)
	{
		value = (unsigned long)stringtable + array[i].n_value;
		type = get_type((unsigned char)(stringtable + array[i].n_type));
		ft_printf("%u %c %s\n", value, type, stringtable + array[i].n_un.n_strx);
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

void						handle_32(char *ptr)
{
	ft_printf("handle 32 bits");
	ptr++;
}

void						nm(char *ptr)
{
	unsigned int						magic_number;

	magic_number = *(uint32_t *) ptr;
	if (magic_number == MH_MAGIC_64 || magic_number == MH_CIGAM_64)
	{
		// handle_header_64(ptr);
	}
	else if (magic_number == MH_MAGIC || magic_number == MH_CIGAM)
	{
		// handle_header_32(ptr);
	}
}

static void					handle_file(char *file_name, t_env *env)
{
	int						fd;
	char					*ptr;
	struct stat				buf;

	ft_printf("fileName: %s\n", file_name);
	// if ((fd = open(file_name, O_RDONLY)) < 0)
	// 	return open_exit(file_name);
	// if (fstat(fd, &buf) < 0)
	// 	return fstat_exit();
	// if ((ptr = mmap(0, buf.st_size, PROT_READ, MAP_PRIVATE, fd, 0)) == MAP_FAILED)
	// 	mmap_munmap_exit("mmap");
	// nm(ptr);
	// if (munmap(ptr, buf.st_size) < 0)
	// 	mmap_munmap_exit("munmap");
};

int							main(int ac, char **av)
{
	int						i;
	t_env					env;

	i = 0;
	if (ac < 2)
	{
		ft_bzero(&env, sizeof(t_env));
		handle_file("a.aout", &env);
	}
	while(++i < ac)
	{
		ft_bzero(&env, sizeof(t_env));
		handle_file(av[i], &env);
	};
	return 0;
};
