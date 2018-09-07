/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   char.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcharvol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/01 18:25:11 by lcharvol          #+#    #+#             */
/*   Updated: 2018/09/01 18:25:21 by lcharvol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_printf.h"

int		print_char(char c)
{
	write(1, &c, 1);
	return (1);
}

int		print_wchar(wchar_t c)
{
	if (c <= 0x7F)
	{
		ft_putchar_fd(c, 1);
		return (1);
	}
	if (c <= 0x7FF)
	{
		ft_putchar_fd((c >> 6) + 0xC0, 1);
		ft_putchar_fd((c & 0x3F) + 0x80, 1);
		return (2);
	}
	if (c <= 0xFFFF)
	{
		ft_putchar_fd((c >> 12) + 0xE0, 1);
		ft_putchar_fd(((c >> 6) & 0x3F) + 0x80, 1);
		ft_putchar_fd((c & 0x3F) + 0x80, 1);
		return (3);
	}
	ft_putchar_fd((c >> 18) + 0xF0, 1);
	ft_putchar_fd(((c >> 12) & 0x3F) + 0x80, 1);
	ft_putchar_fd(((c >> 6) & 0x3F) + 0x80, 1);
	ft_putchar_fd((c & 0x3F) + 0x80, 1);
	return (4);
}

void	if_forest_char(va_list va, t_param param, int *len, int state)
{
	wchar_t	c;

	c = (state < 0) ? va_arg(va, wchar_t) : state;
	c = (state == -2 && param.modif < 0x100) ? (char)c : c;
	*len += print_params(&param, 1, '0', 2);
	*len += print_wchar(c);
	*len += print_params(&param, 1, ' ', -1);
}
