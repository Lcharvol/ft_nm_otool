/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcharvol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/18 20:28:31 by lcharvol          #+#    #+#             */
/*   Updated: 2018/09/18 20:30:54 by lcharvol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/nm.h"

void						handle_header_64(char *ptr, t_env *env)
{
	struct mach_header_64	*header;

	header = (struct mach_header_64 *)ptr;
	env->header_64 = header;
}

void						handle_header_32(char *ptr, t_env *env)
{
	struct mach_header		*header;

	header = (struct mach_header *)ptr;
	env->header_32 = header;
}

void						handle_fat_header(char *ptr, t_env *env)
{
	struct fat_header		*header;

	header = (struct fat_header *)ptr;
	env->header_fat = header;
}

void						handle_sym_tab_header(char *ptr, t_env *env)
{
	struct ar_hdr			*header;

	header = (void *)ptr + SARMAG;
	env->header_sym = header;
}
