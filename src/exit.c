/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcharvol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/18 20:28:03 by lcharvol          #+#    #+#             */
/*   Updated: 2018/09/18 20:28:05 by lcharvol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/nm.h"

int	print_usage(void)
{
	ft_printf("Please give me an arg\n");
	return (EXIT_FAILURE);
}

int	open_exit(char *file_name)
{
	ft_printf("Fail to open '%s' file\n", file_name);
	return (EXIT_FAILURE);
}

int	fstat_exit(void)
{
	ft_printf("fstat: error\n");
	return (EXIT_FAILURE);
}

int	mmap_munmap_exit(char *file_name)
{
	ft_printf("%s: is not an object file\n", file_name);
	return (EXIT_FAILURE);
}
