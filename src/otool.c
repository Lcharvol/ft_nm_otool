/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   otool.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcharvol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/18 20:33:55 by lcharvol          #+#    #+#             */
/*   Updated: 2018/09/19 21:46:12 by lcharvol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/nm.h"

void				otool(char *ptr, t_env *env)
{
	unsigned int	magic_number;

	magic_number = *(uint32_t *)ptr;
	env->magic_number = magic_number;
	if (magic_number == FAT_MAGIC || magic_number == FAT_CIGAM)
		handle_fat_arch(ptr, env);
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
	else
		not_an_object_exit(env->file_name);
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
		return (not_an_object_exit(file_name));
	env->file_size = buf.st_size;
	otool(ptr, env);
	if (munmap(ptr, buf.st_size) < 0)
		return (not_an_object_exit(file_name));
	return (0);
}

int					main(int ac, char **av)
{
	int				i;
	t_env			env;

	i = 0;
	ft_bzero(&env, sizeof(t_env));
	if (ac < 2)
		handle_file("a.aout", &env);
	while (++i < ac)
	{
		env.file_name = av[i];
		env.exec_type = OTOOL;
		env.ar_name = "";
		handle_file(av[i], &env);
	}
	return (0);
}
