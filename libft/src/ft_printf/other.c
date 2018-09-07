/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   other.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcharvol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/01 18:25:55 by lcharvol          #+#    #+#             */
/*   Updated: 2018/09/01 18:25:56 by lcharvol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_printf.h"

int		is_number(const char *f, int *i)
{
	if (f[*i] >= 49 && f[*i] <= 57)
		return (1);
	if (f[*i] == '+' || f[*i] == '-')
		if (f[*i + 1] >= '0' && f[*i + 1] <= '9')
			return (1);
	return (0);
}

int		ft_atoi2(const char *str, int *i)
{
	int		negative;
	int		number;

	negative = 1;
	number = 0;
	if (str[*i] == '+' || str[*i] == '-')
		negative = 44 - str[(*i)++];
	if (str[*i] == '0')
		return (0);
	while (str[*i] < 58 && str[*i] > 47)
		number = number * 10 + str[(*i)++] - 48;
	return (number * negative);
}
