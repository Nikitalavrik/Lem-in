/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   superpos.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlavrine <nlavrine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/16 16:25:00 by nlavrine          #+#    #+#             */
/*   Updated: 2019/08/28 18:19:59 by nlavrine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

t_queue		*remake_path1(t_queue *iter_prev, t_queue *iter_q)
{
	long	dist;
	t_queue	*tmp_queue;

	dist = 0;
	tmp_queue = reshape_queue(iter_prev->next, iter_q->id, &dist);
	while (iter_q)
	{
		push_queue(&tmp_queue, iter_q->name);
		tmp_queue->id = iter_q->id;
		tmp_queue->id_name = iter_q->id_name;
		iter_q = iter_q->prev;
		dist++;
	}
	tmp_queue->dist = dist;
	tmp_queue->is_div = 1;
	return (tmp_queue);
}

void		sort_mult(t_mult_q *mult)
{
	t_mult_q	*iter_m;
	t_mult_q	*iter_l;
	t_queue		*tmp_queue;
	int			id;

	id = 0;
	iter_m = mult;
	while (iter_m)
	{
		iter_l = mult;
		while (iter_l->next)
		{
			if (iter_l->queue->dist > iter_l->next->queue->dist)
			{
				tmp_queue = iter_l->queue;
				iter_l->queue = iter_l->next->queue;
				iter_l->next->queue = tmp_queue;
			}
			iter_l = iter_l->next;
		}
		iter_m->queue->id = id++;
		iter_m = iter_m->next;
	}
}

void		free_and_swap(t_queue **prev_q, t_queue **queue,
						t_queue *tmp_queue1, t_queue *tmp_queue2)
{
	free_queue(prev_q);
	free_queue(queue);
	*prev_q = tmp_queue2;
	*queue = tmp_queue1;
}

void		cut_paths(t_queue **prev_q, t_queue **queue)
{
	t_queue *iter_prev;
	t_queue	*iter_q;
	t_queue *tmp_queue1;
	t_queue *tmp_queue2;

	iter_prev = *prev_q;
	iter_q = *queue;
	while (iter_q->next && !iter_prev->is_div)
	{
		if (check_if_in_queue(&iter_prev, iter_q->id_name))
		{
			tmp_queue1 = remake_path1(iter_prev, iter_q);
			iter_prev = *prev_q;
			iter_q = *queue;
			while (!check_if_in_queue(&iter_q, iter_prev->id_name))
				iter_prev = iter_prev->next;
			tmp_queue2 = reshape_queue(iter_q, iter_prev->id, &iter_q->dist);
			free_and_swap(prev_q, queue, tmp_queue1, tmp_queue2);
			return ;
		}
		iter_q = iter_q ? iter_q->next : NULL;
	}
}

int			analyze_queue(t_mult_q *mult, t_mult_q *last, int *tmp)
{
	int			overlap;
	t_queue		**prev_q;
	t_mult_q	*iter_mult;

	overlap = 0;
	iter_mult = mult;
	prev_q = in_queue(iter_mult, last->queue, &overlap);
	if (overlap == 1)
	{
		ft_printf("dist = %i\n", last->queue->dist);
		free_queue(&last->queue);
		return (0);
	}
	if (overlap > 1)
	{
		cut_paths(prev_q, &last->queue);
		sort_mult(mult);
		recalc(mult, tmp, 0);
	}
	return (1);
}
