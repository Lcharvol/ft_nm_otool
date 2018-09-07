/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strlen.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcharvol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/03 22:46:31 by lcharvol          #+#    #+#             */
/*   Updated: 2018/09/01 18:22:24 by lcharvol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

size_t		ft_strlen(const char *str)
{
	int		i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

size_t		ft_wstrlen(const wchar_t *s)
{
	size_t	i;
	size_t	l;

	i = 0;
	l = 0;
	while (s[i])
	{
		if (s[i] <= 0x7F)
			l += 1;
		else if (s[i] <= 0x7FF)
			l += 2;
		else if (s[i] <= 0xFFFF)
			l += 3;
		else
			l += 4;
		i++;
	}
	return (l);
}
