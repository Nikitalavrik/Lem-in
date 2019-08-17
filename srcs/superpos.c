/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   superpos.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlavrine <nlavrine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/16 16:25:00 by nlavrine          #+#    #+#             */
/*   Updated: 2019/08/17 20:31:09 by nlavrine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

t_queue		*copy_queue_info(t_queue *q1, t_queue *q2, int id)
{
	q1->name = q2->name;
	q1->id = id;
	q1->id_name = q2->id_name;
	return (q1);
}

t_queue		*reshape_queue(t_queue *iter_q, int id, long *dist)
{
	t_queue *new_queue;
	t_queue *tmp_queue;
	t_queue *begin;
	int		dist_l;

	begin = create_queue();
	tmp_queue = begin;
	dist_l = 0;
	while (iter_q)
	{
		if (dist_l)
		{
			new_queue = copy_queue_info(create_queue(), iter_q, id);
			tmp_queue->next = new_queue;
			tmp_queue = tmp_queue->next;
		}
		else
			new_queue = copy_queue_info(tmp_queue, iter_q, id);
		iter_q = iter_q->next;
		dist_l++;
	}
	begin->is_div = 1;
	begin->dist = dist_l;
	*dist = dist_l;
	return (begin);
}

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

	iter_m = mult;
	while (iter_m->next)
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
		iter_m  = iter_m->next;
	}
}

void		free_and_swap(t_queue **prev_q, t_queue **queue,
						t_queue *tmp_queue1, t_queue *tmp_queue2)
{
	// t_queue *iter_q;

	free_queue(prev_q);
	free_queue(queue);
	// if (tmp_queue1->dist < tmp_queue2->dist)
	// {
	// 	swap_queue_id(&tmp_queue1, &tmp_queue2);
	// 	iter_q = tmp_queue1;
	// 	tmp_queue1 = tmp_queue2;
	// 	tmp_queue2 = iter_q;
	// }
	*prev_q = tmp_queue2;
	*queue = tmp_queue1;
}

void		revert_path(t_queue *queue)
{
	t_queue	*iter;

	iter = queue;
	while (iter->prev && iter->prev->prev)
	{
		// ft_printf("name = %s dist = %i\n", iter->room->name, iter->room->dist);
		iter->room->dist = INT16_MAX;
		iter = iter->prev;
	}
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
			// ft_printf("NAME = %s\n", iter_q->name);
			// revert_path(iter_prev);
			// sys_out_queue(*prev_q);
			// sys_out_queue(*queue);
			tmp_queue1 = remake_path1(iter_prev, iter_q);
			iter_prev = *prev_q;
			iter_q = *queue;
			while (!check_if_in_queue(&iter_q, iter_prev->id_name))
				iter_prev = iter_prev->next;
			tmp_queue2 = reshape_queue(iter_q, iter_prev->id, &iter_q->dist);
			// sys_out_queue(tmp_queue1);
			// sys_out_queue(tmp_queue2);
			if (is_identical_queue(tmp_queue1, tmp_queue2))
				return ;
			free_and_swap(prev_q, queue, tmp_queue1, tmp_queue2);
			return ;
		}
		iter_q = iter_q ? iter_q->next : NULL;
	}
}

int			analyze_queue(t_mult_q *mult, t_mult_q *last, int *tmp)
{
	int		overlap;
	t_queue	**prev_q;

	prev_q = in_queue(mult, last->queue, &overlap);
	
	if (overlap == 1)
	{
		ft_printf("dist = %i\n", last->queue->dist);
		// sys_out_queue(last->queue);
		free_queue(&last->queue);
		return (0);
	}
	if (overlap > 1)
	{
		// ft_printf("overlap = %i\n", overlap);
		cut_paths(prev_q, &last->queue);
		sort_mult(mult);
		recalc(mult, tmp, 0);
	}
	return (1);
}
