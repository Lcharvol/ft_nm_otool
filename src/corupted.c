/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corupted.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcharvol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/19 21:37:44 by lcharvol          #+#    #+#             */
/*   Updated: 2018/09/19 21:38:33 by lcharvol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/nm.h"

int	is_corrupted_64(struct segment_command_64	*sc, t_env *env)
{
	if ((sc->fileoff + sc->vmsize) > env->file_size)
		return (1);
	return (0);
}

int	is_corrupted(struct segment_command	*sc, t_env *env)
{
	if ((sc->fileoff + sc->vmsize) > env->file_size)
		return (1);
	return (0);
}
