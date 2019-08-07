/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calculator.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlavrine <nlavrine@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/29 13:33:25 by nlavrine          #+#    #+#             */
/*   Updated: 2019/07/29 13:33:26 by nlavrine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int		mod(int a)
{
	return (a < 0 ? -a : a);
}

t_queue	*copy_queue(t_queue *queue)
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
	}
	return (mult_ants);
}

int		*counting_ants_path(int *tmp, int ants, int len)
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
	i = 0;
	ft_printf("PATHS : ");
	while (i < len)
	{
		ft_printf("%i ", count_path[i]);
		i++;
	}
	ft_printf("\n");
	return (count_path);
}

int		free_end(t_mult_q **mult, int len)
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
	// free_mult(&iter, 0);
	iter_next = iter->next;
	iter->next = NULL;
	free_mult(&iter_next);
	// iter = iter_next;
	// while (iter)
	// {
	// 	iter_next = iter->next;
	// 	free_queue(&iter->queue);
	// 	ft_memdel((void **)&iter);
	// 	iter = iter_next;
	// }
	// system("leaks lem-in");
	// exit(0);
	return (1);
}

t_mult_q	*calculator(t_mult_q *mult, int ants, int *lines)
{
	int			i;
	int			tmp[100];
	t_mult_q	*iter;
	int			tmp_ants;
	int			*count_paths;
	t_mult_q	*ants_queue;

	i = 0;
	iter = mult;
	tmp_ants = ants;
	ft_bzero(tmp, sizeof(tmp));
	*lines = 0;
	while (ants > 0)
	{
		if (iter->next)
		{
			tmp[i] = iter->next->queue->dist - iter->queue->dist;
			if (((i + 1) * tmp[i]) > ants)
			{
				
				tmp[i] = (ants / (i + 1)) + (ants % (i + 1) ? 1 : 0);
				// ft_printf("ants = %i f = %i tmp[%i] = %i\n", ants, ants / (i + 1), i, tmp[i]);
				*lines =  tmp[i] + iter->queue->dist - 1;
				ants = 0;
			}
			else
				ants -= (i + 1) * tmp[i];
			iter = iter->next;
			i++;
		}
		else
		{
			tmp[i] = (ants / (i + 1)) + (ants % (i + 1) ? 1 : 0);
			*lines = tmp[i] + iter->queue->dist - 1;
			i++;
			// ft_printf("111111\n");
			break ;
		}
	}
	sys_out_dist(tmp, i);
	// ft_printf("lines = %i\n", lines);
	count_paths = counting_ants_path(tmp, tmp_ants, i);
	free_end(&mult, i);

	ants_queue = create_ants(mult, count_paths, tmp_ants);
	ft_memdel((void **)&count_paths);
	return (ants_queue);
}