/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fat.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcharvol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/19 21:41:32 by lcharvol          #+#    #+#             */
/*   Updated: 2018/09/19 21:44:14 by lcharvol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/nm.h"

static int				handle_my_cpu(t_env *env, unsigned long i,
		struct fat_header *header_fat, char *ptr)
{
	struct fat_arch		*arch;
	unsigned long		arch_offset;
	unsigned long		size;
	cpu_type_t			cputype;

	arch = (void *)header_fat + sizeof(struct fat_header) +
		(i * sizeof(struct fat_arch));
	cputype = header_fat->magic == FAT_MAGIC ? arch->cputype :
		swap_bigendian_littleendian(arch->cputype, sizeof(arch->cputype));
	arch_offset = header_fat->magic == FAT_MAGIC ? arch->offset :
		swap_bigendian_littleendian(arch->offset, sizeof(arch->offset));
	size = header_fat->magic == FAT_MAGIC ? arch->size :
		swap_bigendian_littleendian(arch->size, sizeof(arch->size));
	env->header_32 = (struct mach_header *)((void *)ptr + arch_offset);
	if (cputype == MY_CPU_TYPE)
	{
		if (arch_offset + size > env->file_size)
			return (-1);
		nm((void *)ptr + arch_offset, env);
		return (1);
	}
	return (0);
}

void					handle_fat_arch(char *ptr, t_env *env)
{
	struct fat_header	*header_fat;
	unsigned long		nfat_arch;
	unsigned long		i;
	int					ret;

	i = -1;
	handle_fat_header(ptr, env);
	header_fat = env->header_fat;
	nfat_arch = header_fat->magic == FAT_MAGIC ? header_fat->nfat_arch :
		swap_bigendian_littleendian(header_fat->nfat_arch,
				sizeof(header_fat->nfat_arch ));
	while (++i < nfat_arch)
	{
		if ((ret = handle_my_cpu(env, i, header_fat, ptr)) == 1)
			return ;
		if (ret == -1)
			return (corrupted_exit(env->file_name));
	}
	i = -1;
}
