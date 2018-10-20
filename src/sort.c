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

t_outputs			*remove_no_address_doublon(t_outputs *outputs)
{
	t_outputs		*tmp;
	t_outputs		*prev;

	tmp = outputs;
	prev = tmp;
	while(outputs)
	{
		if(outputs->next)
		{
			if((ft_strcmp(outputs->name, outputs->next->name) == 0
				&& outputs->n_value == 0) || ft_strlen(outputs->name) > STR_MAX)
			{
				outputs = prev;
				outputs->next = outputs->next->next;
			}
		}
		prev = outputs;
		outputs = outputs->next;
	}
	outputs = tmp;
	return outputs;
}

t_outputs			*sort_outputs_by_address(t_outputs *outputs)
{
	t_outputs		*tmp;
	t_outputs		*tmp2;

	tmp = outputs;
	tmp2 = tmp->next;
	while(outputs)
	{
		if(outputs->next)
		{
			if(ft_strcmp(outputs->name, outputs->next->name) == 0
				&& outputs->n_value > outputs->next->n_value)
			{
				tmp2 = outputs;
				tmp2->next = outputs->next->next;
				outputs = tmp2;
				outputs = tmp;
			}
		}
		tmp2 = outputs;
		outputs = outputs->next;
	}
	outputs = tmp;
	return remove_no_address_doublon(outputs);
}

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
	return (sort_outputs_by_address(outputs));
}
