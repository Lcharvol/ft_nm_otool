/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcharvol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/19 14:39:01 by lcharvol          #+#    #+#             */
/*   Updated: 2018/10/19 14:41:17 by lcharvol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/nm.h"

void				swap(t_outputs *a, t_outputs *b)
{
	unsigned long	tmp_n_value;
	unsigned char	tmp_n_type;
	char			*tmp_name;

	tmp_n_value = a->n_value;
	tmp_n_type = a->n_type;
	tmp_name = a->name;
	a->n_value = b->n_value;
	a->n_type = b->n_type;
	a->name = b->name;
	b->n_value = tmp_n_value;
	b->n_type = tmp_n_type;
	b->name = tmp_name;
}

t_outputs			*sort_outputs(t_outputs *outputs)
{
	t_outputs		*tmp;

	tmp = outputs;
	while (outputs->next)
	{
		if (ft_strcmp(outputs->name, outputs->next->name) > 0)
		{
			swap(outputs, outputs->next);
			outputs = tmp;
		}
		else
			outputs = outputs->next;
	}
	outputs = tmp;
	return (outputs);
}
