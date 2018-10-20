/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nm.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcharvol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/19 15:10:36 by lcharvol          #+#    #+#             */
/*   Updated: 2018/10/19 15:15:20 by lcharvol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/nm.h"

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
	while (i < ncmds)
	{
		if (lc->cmd == LC_SYMTAB)
		{
			sym = (struct symtab_command *)lc;
			env->outputs = save_outputs_64(sym->nsyms, sym->symoff,
					sym->stroff, ptr);
			sort_outputs(env->outputs);
			print_outputs_64(env);
			break ;
		}
		lc = (void *)lc + lc->cmdsize;
		i++;
	}
}

void						handle_32(char *ptr, t_env *env)
{
	int						ncmds;
	int						i;
	struct mach_header		*header;
	struct load_command		*lc;
	struct symtab_command	*sym;

	i = 0;
	header = env->header_32;
	ncmds = header->magic == MH_MAGIC ? header->ncmds :
		swap_bigendian_littleendian(header->ncmds, sizeof(header->ncmds));
	lc = (void *)ptr + sizeof(*header);
	while (i < ncmds)
	{
		if (lc->cmd == LC_SYMTAB)
		{
			sym = (struct symtab_command *)lc;
			env->outputs = save_outputs_32(sym->nsyms, sym->symoff,
					sym->stroff, ptr);
			sort_outputs(env->outputs);
			print_outputs_32(env);
			break ;
		}
		lc = (void *)lc + lc->cmdsize;
		i++;
	}
}

void						nm(char *ptr, t_env *env)
{
	unsigned int	magic_number;

	magic_number = *(uint32_t *)ptr;
	env->magic_number = magic_number;
	if (magic_number == FAT_MAGIC || magic_number == FAT_CIGAM)
		handle_fat_arch(ptr, env);
	else if (magic_number == MH_MAGIC_64 || magic_number == MH_CIGAM_64)
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
	env->file_name = file_name;
	nm(ptr, env);
	if (munmap(ptr, buf.st_size) < 0)
		return (not_an_object_exit(file_name));
	return (0);
}

int							main(int ac, char **av)
{
	int						i;
	t_env					env;

	i = 0;
	ft_bzero(&env, sizeof(t_env));
	env.exec_type = NM;
	if (ac < 2)
		handle_file("a.aout", &env);
	while (++i < ac)
	{
		env.exec_type = NM;
		handle_file(av[i], &env);
		ft_bzero(&env, sizeof(t_env));
	}
	return (0);
}
