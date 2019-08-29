/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   usefull_staff.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlavrine <nlavrine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/08 19:35:36 by nlavrine          #+#    #+#             */
/*   Updated: 2019/08/29 14:19:21 by nlavrine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int			recalc(t_mult_q *mult, int *tmp, int end)
{
	t_mult_q	*iter_m;
	int			i;

	i = 0;
	iter_m = mult;
	ft_bzero(tmp, sizeof(tmp));
	mult->iter_ants = mult->ants;
	while (iter_m)
	{
		if (!iter_m->next)
			iter_m->prev->end = end;
		if (i)
			mult->lines = relevance(tmp, i, &mult->iter_ants, iter_m->prev);
		i++;
		iter_m = iter_m->next;
	}
	return (i);
}

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

int			check_splited(char *line)
{
	int i;
	int	count;

	i = 0;
	count = 0;
	while (line[i])
	{
		if (line[i] == '-')
			count++;
		if (count > 1)
			return (0);
		i++;
	}
	return (1);
}

t_queue		**in_queue(t_mult_q *iter_mult, t_queue *queue, int *i)
{
	t_queue		*q1;
	t_queue		*q2;

	q1 = queue;
	while (iter_mult->next)
	{
		q2 = iter_mult->queue;
		while (q2->next)
		{
			q1 = queue;
			while (q1->next)
			{
				if (q1->id_name == q2->id_name)
				{
					(*i) = q1->prev->id_name == q2->next->id_name ? 2 : 1;
					return (&iter_mult->queue);
				}
				q1 = q1->next;
			}
			q2 = q2->next;
		}
		iter_mult = iter_mult->next;
	}
	return (NULL);
}
