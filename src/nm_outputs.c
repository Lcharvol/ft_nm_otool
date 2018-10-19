/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nm_outputs.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcharvol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/19 15:15:57 by lcharvol          #+#    #+#             */
/*   Updated: 2018/10/19 15:21:37 by lcharvol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/nm.h"

void				print_outputs_32(t_env *env)
{
	t_outputs		*outputs;

	outputs = env->outputs;
	while (outputs)
	{
		if (outputs->n_value == 0)
			ft_printf("         %c %s\n",
				outputs->n_type, outputs->name);
		else
			ft_printf("%08lx %c %s\n", outputs->n_value,
				outputs->n_type, outputs->name);
		outputs = outputs->next;
	}
}

void				print_outputs_64(t_env *env)
{
	t_outputs		*outputs;

	outputs = env->outputs;
	while (outputs)
	{
		if (outputs->n_value == 0)
			ft_printf("                 %c %s\n",
				outputs->n_type, outputs->name);
		else
			ft_printf("%016lx %c %s\n", outputs->n_value,
				outputs->n_type, outputs->name);
		outputs = outputs->next;
	}
}

static t_outputs	*add_output(unsigned long n_value, unsigned char n_type,
		char *name, t_outputs *outputs)
{
	t_outputs		*tmp;
	t_outputs		*new;

	tmp = outputs;
	while (outputs->next)
		outputs = outputs->next;
	if (outputs->used != 1)
	{
		outputs->n_value = n_value;
		outputs->n_type = n_type;
		outputs->used = 1;
		outputs->name = name;
		outputs->next = NULL;
		return (outputs);
	}
	new = (t_outputs *)malloc(sizeof(t_outputs));
	new->n_value = n_value;
	new->n_type = n_type;
	new->used = 1;
	new->name = name;
	new->next = NULL;
	outputs->next = new;
	return (tmp);
}

t_outputs			*save_outputs_64(int nsyms, int symoff,
		int stroff, char *ptr)
{
	int				i;
	char			*stringtable;
	struct nlist_64	*array;
	t_outputs		*outputs;
	char			type;

	i = -1;
	array = (void *)ptr + symoff;
	stringtable = (void *)ptr + stroff;
	outputs = (t_outputs *)malloc(sizeof(*outputs));
	outputs->next = NULL;
	while (++i < nsyms)
	{
		type = get_type_64(ptr, array[i].n_type, array[i].n_sect);
		if (type != 'u')
			outputs = add_output(array[i].n_value, type, stringtable +
					array[i].n_un.n_strx, outputs);
	}
	return (outputs);
}

t_outputs			*save_outputs_32(int nsyms, int symoff,
		int stroff, char *ptr)
{
	int				i;
	char			*stringtable;
	struct nlist	*array;
	t_outputs		*outputs;
	char			type;

	i = -1;
	array = (void *)ptr + symoff;
	stringtable = (void *)ptr + stroff;
	outputs = (t_outputs *)malloc(sizeof(*outputs));
	outputs->next = NULL;
	while (++i < nsyms)
	{
		type = get_type_32(ptr, array[i].n_type, array[i].n_sect);
		if (type != 'u')
			outputs = add_output(array[i].n_value, type, stringtable +
					array[i].n_un.n_strx, outputs);
	}
	return (outputs);
}
