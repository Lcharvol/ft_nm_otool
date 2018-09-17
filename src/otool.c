#include "../includes/nm.h"					

// void						handle_text_section_fat_arch_64(char *ptr, unsigned long magic)
// {
// 	struct segment_command_64	*sc;
// 	struct section_64		*sects;
// 	struct mach_header_64	*header;
// 	uint32_t 					i;
// 	uint32_t				ncmds;
// 	uint32_t				cmdsize;

// 	i = 0;
// 	header = (struct mach_header_64 *)ptr;
// 	ncmds = header->ncmds;
// 	ft_printf("ncmds: %d\n", ncmds);
// 	sc = (void *)ptr + sizeof(*header);
// 	while(i < ncmds)
// 	{
// 		// if(sc->cmd == LC_SEGMENT_64)
// 		// {
// 		// 	i = 0;
// 		// 	sects = (void *)sc +sizeof(struct segment_command_64);
// 		// 	while(i < sc->nsects)
// 		// 	{
// 		// 		if(ft_strcmp(sects->sectname,SECT_TEXT) == 0)
// 		// 			print_text_section_64(sects, ptr);
// 		// 		sects = (void *)sects + sizeof(struct section_64);
// 		// 		i++;
// 		// 	}
// 		// };
// 		i++;
// 		ft_printf("sc->cmdsize: ", sc->cmdsize);
// 		sc = (void *)sc + sc->cmdsize;
// 	}
// }

void						handle_fat_arch(char *ptr, t_env *env)
{
	struct fat_header	*header_fat;
	struct mach_header	*mach_header;
	struct fat_arch		*arch;
	unsigned long		nfat_arch;
	unsigned long		arch_offset;
	unsigned long		i;

	i = 0;
	header_fat = env->header_fat;
	nfat_arch = header_fat->magic == FAT_MAGIC ? header_fat->nfat_arch :
		swap_bigendian_littleendian(header_fat->nfat_arch , sizeof(header_fat->nfat_arch ));
	while(i < nfat_arch)
	{
		arch = (void *)header_fat + sizeof(struct fat_header) + (i * sizeof(struct fat_arch));
		arch_offset = header_fat->magic == FAT_MAGIC ? arch->offset : swap_bigendian_littleendian(arch->offset, sizeof(arch->offset));
		mach_header = (struct mach_header *)((void *)ptr + arch_offset);
		env->header_32 = mach_header;
		ft_printf("ON PASSSSSEEEEEEEE\n");
		handle_text_section_32((void *)ptr + arch_offset, env);
		i++;
	}
}

static void					otool(char *ptr, t_env *env)
{
	unsigned int			magic_number;

	magic_number = *(uint32_t *)ptr;
	env->magic_number = magic_number;
	if (magic_number == FAT_MAGIC || magic_number == FAT_CIGAM)
	{
		handle_fat_header(ptr, env);
		handle_fat_arch(ptr, env);
	}
	else if (magic_number == MH_MAGIC_64 || magic_number == MH_CIGAM_64)
	{
		handle_header_64(ptr, env);
		handle_text_section_64(ptr, env);
	}
	else if (magic_number == MH_MAGIC || magic_number == MH_CIGAM)
	{
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
		return mmap_munmap_exit(file_name);
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
