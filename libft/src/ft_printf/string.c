/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcharvol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/01 18:26:10 by lcharvol          #+#    #+#             */
/*   Updated: 2018/09/01 18:26:11 by lcharvol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_printf.h"

void	print_wstr(wchar_t *str, int *len, int n)
{
	int		i;
	int		b;

	i = 0;
	b = 0;
	while (str[i] && b < n)
		b += print_wchar(str[i++]);
	*len += b;
}

void	print_str(char *str, int *len, int n)
{
	int		i;

	i = 0;
	while (str[i] && i < n)
		*len += print_char(str[i++]);
}

void	ft_wstr(va_list va, t_param p, int *len)
{
	wchar_t	*s;
	int		l;
	int		n;

	s = va_arg(va, wchar_t*);
	if (s == NULL)
		s = L"(null)";
	l = (s != NULL) ? (int)ft_wstrlen(s) : 0;
	n = (p.prec < l && p.bool) ? p.prec : l;
	p.prec = (p.prec < l) ? p.prec : l;
	*len += print_params(&p, n, '0', 2);
	*len += print_params(&p, n, ' ', 1);
	print_wstr(s, len, n);
	*len += print_params(&p, n, ' ', -1);
}

void	ft_str(va_list va, t_param p, int *len)
{
	char	*s;
	int		l;
	int		n;

	s = va_arg(va, char*);
	if (s == NULL)
		s = "(null)";
	l = (s != NULL) ? (int)ft_strlen(s) : 0;
	n = (p.prec < l && p.bool) ? p.prec : l;
	p.prec = (p.prec < l) ? p.prec : l;
	p.save = p.prec;
	*len += print_params(&p, n, '0', 2);
	*len += print_params(&p, n, ' ', 1);
	print_str(s, len, n);
	*len += print_params(&p, n, ' ', -1);
}

void	if_forest_string(va_list va, t_param param, int *len, int type)
{
	if (type == 'S' || param.modif)
		ft_wstr(va, param, len);
	else
		ft_str(va, param, len);
}
