#include "../includes/nm.h"

unsigned char				get_type(unsigned char type, int n_sect)
{

	if (n_sect == NO_SECT)
	{
		if ((type & N_TYPE) == N_UNDF)
			return ('U');
		else if ((type & N_TYPE) == N_ABS)
			return ((type & N_EXT) ? 'A' : 'a');
	}
	return '?';
};

void						print_output_64(int nsyms, int symoff, int stroff, char *ptr)
{
	int						i;
	char					*stringtable;
	struct nlist_64			*array;
	unsigned long			n_value;

	i = -1;
	array = (void *)ptr + symoff;
	stringtable = (void *)ptr + stroff;
	while(++i < nsyms)
	{
		n_value = array[i].n_value;
		if(n_value == 0)
			ft_printf("                 %c %s\n",
				get_type(array[i].n_type, array[i].n_sect), stringtable + array[i].n_un.n_strx);
		else
			ft_printf("%016lx %c %s\n", n_value,
				get_type(array[i].n_type, array[i].n_sect), stringtable + array[i].n_un.n_strx);
	}
}

void						print_output_32(int nsyms, int symoff, int stroff, char *ptr)
{
	int						i;
	char					*stringtable;
	struct nlist			*array;
	unsigned long			n_value;

	i = -1;
	array = (void *)ptr + symoff;
	stringtable = (void *)ptr + stroff;
	while(++i < nsyms)
	{
		n_value = array[i].n_value;
		if(n_value == 0)
			ft_printf("                 %c %s\n",
				get_type(array[i].n_type, array[i].n_sect), stringtable + array[i].n_un.n_strx);
		else
			ft_printf("%016lx %c %s\n", n_value,
				get_type(array[i].n_type, array[i].n_sect), stringtable + array[i].n_un.n_strx);
	}
}

void						handle_64(char *ptr, t_env *env)
{
	int						ncmds;
	int						i;
	struct mach_header_64	*header;
	struct load_command		*lc;
	struct symtab_command	*sym;

	i = 0;
	header = env->header_64;
	ncmds = header->magic == MH_MAGIC_64 ? header->ncmds :
		swap_bigendian_littleendian(header->ncmds, sizeof(header->ncmds));
	lc = (void *)ptr + sizeof(*header);
	while(i < ncmds)
	{
		if(lc->cmd == LC_SYMTAB)
		{
			sym = (struct symtab_command *)lc;
			print_output_64(sym->nsyms, sym->symoff, sym->stroff, ptr);
			break ;
		};
		lc = (void *)lc + lc->cmdsize;
		i++;
	}
}

void						handle_32(char *ptr, t_env *env)
{
	int						ncmds;
	int						i;
	struct mach_header	*header;
	struct load_command		*lc;
	struct symtab_command	*sym;

	i = 0;
	header = env->header_32;
	ncmds = header->magic == MH_MAGIC ? header->ncmds :
		swap_bigendian_littleendian(header->ncmds, sizeof(header->ncmds));
	lc = (void *)ptr + sizeof(*header);
	while(i < ncmds)
	{
		if(lc->cmd == LC_SYMTAB)
		{
			sym = (struct symtab_command *)lc;
			print_output_32(sym->nsyms, sym->symoff, sym->stroff, ptr);
			break ;
		};
		lc = (void *)lc + lc->cmdsize;
		i++;
	}
}

void						nm(char *ptr, t_env *env)
{
	unsigned int	magic_number;

	magic_number = *(uint32_t *)ptr;
	env->magic_number = magic_number;
	// if (magic_number == FAT_MAGIC || magic_number == FAT_CIGAM)
	// 	handle_fat_arch(ptr, env);
	if (magic_number == MH_MAGIC_64 || magic_number == MH_CIGAM_64)
	{
		handle_header_64(ptr, env);
		handle_64(ptr, env);
	}
	else if (magic_number == MH_MAGIC || magic_number == MH_CIGAM)
	{
		handle_header_32(ptr, env);
		handle_32(ptr, env);
	}
	else if (is_sym_tab(ptr) == 0)
	{
		handle_sym_tab_header(ptr, env);
		ft_printf("sym tab\n");
		// handle_sym_tab(ptr, env);
	}
	else
		not_an_object_exit(env->file_name);
}

static int					handle_file(char *file_name, t_env *env)
{
	int				fd;
	char			*ptr;
	struct stat		buf;

	if ((fd = open(file_name, O_RDONLY)) < 0)
		return (open_exit(file_name));
	if (fstat(fd, &buf) < 0)
		return (fstat_exit());
	if ((ptr = mmap(0, buf.st_size, PROT_READ, MAP_PRIVATE, fd, 0))
			== MAP_FAILED)
		return (not_an_object_exit(file_name));
	env->file_size = buf.st_size;
	nm(ptr, env);
	if (munmap(ptr, buf.st_size) < 0)
		return (not_an_object_exit(file_name));
	return (0);
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
