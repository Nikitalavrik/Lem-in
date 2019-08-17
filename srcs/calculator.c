/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calculator.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlavrine <nlavrine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/29 13:33:25 by nlavrine          #+#    #+#             */
/*   Updated: 2019/08/17 20:23:53 by nlavrine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

t_queue		*copy_queue(t_queue *queue)
{
	t_queue	*begin;
	t_queue	*c_queue;
	t_queue	*prev;
	t_queue	*c_begin;

	begin = queue;
	c_queue = NULL;
	prev = NULL;
	while (begin)
	{
		c_queue = create_queue();
		c_queue->name = ft_strdup(begin->name);
		c_queue->id = begin->id;
		c_queue->id_name = begin->id_name;
		if (prev)
			prev->next = c_queue;
		else
			c_begin = c_queue;
		prev = c_queue;
		begin = begin->next;
	}
	return (c_begin);
}

t_mult_q	*create_ants(t_mult_q *mult, int *paths, int ants)
{
	t_mult_q	*mult_ants;
	t_mult_q	*iter_ants;
	t_mult_q	*iter_queue;
	int			i;

	i = 0;
	mult_ants = create_mult();
	iter_ants = mult_ants;
	iter_queue = mult;
	while (i < ants)
	{
		if (!iter_queue)
			iter_queue = mult;
		if (paths[iter_queue->queue->id])
		{
			if (i)
				iter_ants = add_mult(iter_ants);
			iter_ants->id = i;
			iter_ants->queue = copy_queue(iter_queue->queue);
			paths[iter_queue->queue->id]--;
			i++;
		}
		iter_queue = iter_queue->next;
		// ft_printf(" i %i\n", i);
	}
	return (mult_ants);
}

int			*counting_ants_path(int *tmp, int ants, int len)
{
	int		*count_path;
	int		i;
	int		j;

	i = 0;
	count_path = ft_memalloc(sizeof(int) * len);
	while (i < len)
	{
		j = i;
		while (j < len)
		{
			count_path[i] += tmp[j];
			j++;
		}
		if (count_path[i] > ants)
			count_path[i]--;
		ants -= count_path[i];
		i++;
	}
	return (count_path);
}

int			free_end(t_mult_q **mult, int len)
{
	int			i;
	t_mult_q	*iter;
	t_mult_q	*iter_next;

	i = 0;
	iter = *mult;
	while (i < len - 1)
	{
		iter = iter->next;
		i++;
	}
	iter_next = iter->next;
	iter->next = NULL;
	free_mult(&iter_next);
	return (1);
}

void		calculator(t_mult_q *mult, int end_id, int *tmp, int len)
{
	int			*count_paths;
	t_mult_q	*ants_queue;

	count_paths = counting_ants_path(tmp, mult->ants, len);
	free_end(&mult, len);
	
	// ft_printf("ant = %i\n", mult->ants);
	sys_out_dist(count_paths, len);
	ants_queue = create_ants(mult, count_paths, mult->ants);
	ft_memdel((void **)&count_paths);
	print_res(ants_queue, end_id, mult->lines);
	end_id = 0;
	ft_printf("lines = %i\n", mult->lines);
	free_mult(&ants_queue);
	free_mult(&mult);
}
