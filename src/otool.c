#include "../includes/nm.h"

void	print_text_section_64(struct section_64	*sects)
{
	int i;

	i = 0;
	ft_printf("%016lx        ", sects->addr);
	while(i < sects->size)
	{
		if (i % 16 == 0 && i != 0)
			ft_printf("\n%016lx	", sects->addr + i);
		i++;
	}
}

void	handle_text_section_64(char *ptr, t_env *env)
{
	struct segment_command_64	*sc;
	struct section_64		*sects;
	struct mach_header_64	*header;
	uint32_t 					i;
	uint32_t				ncmds;

	i = 0;
	header = (struct mach_header_64 *)ptr;
	ncmds = header->ncmds;
	sc = (void *)ptr + sizeof(*header);

	while(i < ncmds)
	{
		if(ft_strcmp(sc->segname,SEG_TEXT) == 0)
		{
			i = 0;
			sects = (void *)sc +sizeof(struct segment_command_64);
			while(i < sc->nsects)
			{
				if(ft_strcmp(sects->sectname,SECT_TEXT) == 0)
					print_text_section_64(sects);
				sects = (void *)sects + sizeof(struct section_64);
				i++;
			}
		};
		i++;
		sc = (void *)sc + sc->cmdsize;
	}
}

void	handle_text_section_32(char *ptr, t_env *env)
{
	struct segment_command	*sc;
	int						header_size;
	uint32_t 					i;
	uint32_t				ncmds;

	i = 0;
	header_size = env->arch_type == ARCH_32 ? sizeof(env->header_32) : sizeof(env->header_64);
	ncmds = env->arch_type == ARCH_32 ? env->header_32->ncmds : env->header_64->ncmds;
	sc = (void *)ptr + header_size;

	while(i < ncmds)
	{
		if(ft_strcmp(sc->segname,SEG_TEXT) == 0)
		{
			
		};
		i++;
		sc = (void *)sc + sizeof(sc);
	}
}

void	otool(char *ptr, t_env *env)
{
	unsigned int						magic_number;
	unsigned int						is_swap;

	magic_number = *(uint32_t *) ptr;
	is_swap = magic_number == MH_CIGAM || magic_number == MH_CIGAM_64;
	if (magic_number == MH_MAGIC_64 || magic_number == MH_CIGAM_64)
	{
		env->arch_type = ARCH_64;
		env->is_swap = is_swap;
		handle_header_64(ptr, env);
		handle_text_section_64(ptr, env);
	}
	else if (magic_number == MH_MAGIC || magic_number == MH_CIGAM)
	{
		env->arch_type = ARCH_32;
		env->is_swap = is_swap;
		handle_header_32(ptr, env);
		handle_text_section_32(ptr, env);
	}
}

static int					handle_file(char *file_name, t_env *env)
{
	int						fd;
	char					*ptr;
	struct stat				buf;

	if ((fd = open(file_name, O_RDONLY)) < 0)
		return open_exit(file_name);
	if (fstat(fd, &buf) < 0)
		return fstat_exit();
	if ((ptr = mmap(0, buf.st_size, PROT_READ, MAP_PRIVATE, fd, 0)) == MAP_FAILED)
		return mmap_munmap_exit("mmap");
	ft_printf("%s:\n", file_name);
	ft_printf("Contents of (__TEXT,__text) section\n");
	otool(ptr, env);
	if (munmap(ptr, buf.st_size) < 0)
		return mmap_munmap_exit("munmap");
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
		env.file_name = av[i];
		env.exec_type = OTOOL;
		handle_file(av[i], &env);
	};
	return 0;
};
