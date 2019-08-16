/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sys_output.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlavrine <nlavrine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/19 15:12:40 by nlavrine          #+#    #+#             */
/*   Updated: 2019/08/16 11:42:54 by nlavrine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	sys_out_rooms(t_rooms *begin)
{
	t_rooms *tmp;
	t_rooms *tmp_sub;

	tmp = begin;
	while (tmp)
	{
		ft_printf("name = |%s| id = |%i| dist = |%i|\n",
										tmp->name, tmp->id, tmp->dist);
		tmp_sub = tmp->sub;
		while (tmp_sub)
		{
			ft_printf("|%s| path = %i\n", tmp_sub->name, tmp_sub->path);
			tmp_sub = tmp_sub->next;
		}
		ft_printf("PREV : ");
		if (tmp->prev)
			ft_printf("{%s}", tmp->prev->name);
		ft_printf("\n------------------\n");
		tmp = tmp->next;
	}
	ft_printf("*********************************\n");
}

void	sys_out_dist(int *dist, int n)
{
	int	i;

	i = 0;
	ft_printf("DIST : ");
	while (i < n)
	{
		ft_printf("%i ", dist[i]);
		i++;
	}
	ft_printf("\n");
}

void	sys_out_queue(t_queue *queue)
{
	t_queue *iter_queue;

	iter_queue = queue;
	ft_printf("dist %i\nQUEUE : ", iter_queue->dist);
	while (iter_queue && iter_queue->name)
	{
		ft_printf("%s ", iter_queue->name);
		iter_queue = iter_queue->next;
	}
	ft_printf("\n");
}

void	sys_out_mult(t_mult_q *mult)
{
	t_mult_q	*iter;

	iter = mult;
	while (iter)
	{
		sys_out_queue(iter->queue);
		iter = iter->next;
	}
	ft_printf("~~~~~~~~~~~~~~~~~\n");
}
