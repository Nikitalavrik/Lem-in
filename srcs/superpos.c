/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   superpos.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlavrine <nlavrine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/16 16:25:00 by nlavrine          #+#    #+#             */
/*   Updated: 2019/08/16 17:51:25 by nlavrine         ###   ########.fr       */
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

void		free_and_swap(t_queue **prev_q, t_queue **queue,
						t_queue *tmp_queue1, t_queue *tmp_queue2)
{
	t_queue *iter_q;

	free_queue(prev_q);
	free_queue(queue);
	if (tmp_queue1->dist < tmp_queue2->dist)
	{
		swap_queue_id(&tmp_queue1, &tmp_queue2);
		iter_q = tmp_queue1;
		tmp_queue1 = tmp_queue2;
		tmp_queue2 = iter_q;
	}
	*prev_q = tmp_queue2;
	*queue = tmp_queue1;
}

int			analyze_queue(t_queue **prev_q, t_queue **queue)
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
			ft_printf("NAME = %s\n", iter_q->name);
			tmp_queue1 = remake_path1(iter_prev, iter_q);
			iter_prev = *prev_q;
			iter_q = *queue;
			while (!check_if_in_queue(&iter_q, iter_prev->id_name))
				iter_prev = iter_prev->next;
			tmp_queue2 = reshape_queue(iter_q, iter_prev->id, &iter_q->dist);
			if (is_identical_queue(tmp_queue1, tmp_queue2))
				return (0);
			free_and_swap(prev_q, queue, tmp_queue1, tmp_queue2);
			return (0);
		}
		iter_q = iter_q ? iter_q->next : NULL;
	}
	return (0);
}
