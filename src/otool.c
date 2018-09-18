/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   otool.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcharvol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/18 20:33:55 by lcharvol          #+#    #+#             */
/*   Updated: 2018/09/18 20:37:15 by lcharvol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/nm.h"

void				handle_ran_lib(void)
{
	ft_printf("HANDLE RAN LIB\n");
}

void				handle_ran_lib_64(void)
{
	ft_printf("HANDLE RAN LIB_64\n");
}

void				handle_sym_tab(char *ptr, t_env *env)
{
	void			*new_ptr;
	uint32_t		*size;
	struct ar_hdr	*header;

	header = env->header_sym;
	new_ptr = (void *)header + sizeof(*header);
	size = ((void*)new_ptr + 20);
	if (ft_strcmp(new_ptr, SYMDEF) == 0 ||
			ft_strcmp(new_ptr, SYMDEF_SORTED) == 0)
		handle_ran_lib();
	else if (ft_strcmp(new_ptr, SYMDEF_64) == 0 ||
			ft_strcmp(new_ptr, SYMDEF_64_SORTED) == 0)
		handle_ran_lib_64();
}

void				otool(char *ptr, t_env *env)
{
	unsigned int	magic_number;

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
	else if (is_sym_tab(ptr) == 0)
	{
		handle_sym_tab_header(ptr, env);
		handle_sym_tab(ptr, env);
	}
}

static int			handle_file(char *file_name, t_env *env)
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
		return (mmap_munmap_exit(file_name));
	otool(ptr, env);
	if (munmap(ptr, buf.st_size) < 0)
		return (mmap_munmap_exit("munmap"));
	return (0);
}

int					main(int ac, char **av)
{
	int				i;
	t_env			env;

	i = 0;
	if (ac < 2)
	{
		ft_bzero(&env, sizeof(t_env));
		handle_file("a.aout", &env);
	}
	while (++i < ac)
	{
		ft_bzero(&env, sizeof(t_env));
		env.file_name = av[i];
		env.exec_type = OTOOL;
		handle_file(av[i], &env);
	}
	return (0);
}
