#include "../includes/nm.h"

static void					otool(char *ptr, t_env *env)
{
	unsigned int			magic_number;
	unsigned int			is_swap;

	magic_number = *(uint32_t *)ptr;
	is_swap = magic_number == MH_CIGAM || magic_number == MH_CIGAM_64;
	if (magic_number == MH_MAGIC_64 || magic_number == MH_CIGAM_64)
	{
		env->arch_type = ARCH_64;
		env->is_swap = is_swap;
		handle_header_64(ptr, env);
		handle_text_section_64(ptr);
	}
	else if (magic_number == MH_MAGIC || magic_number == MH_CIGAM)
	{
		env->arch_type = ARCH_32;
		env->is_swap = is_swap;
		handle_header_32(ptr, env);
		handle_text_section_32(ptr);
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
		return mmap_munmap_exit(file_name);
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
