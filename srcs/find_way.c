/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_way.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlavrine <nlavrine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/25 09:48:28 by nlavrine          #+#    #+#             */
/*   Updated: 2019/08/17 20:33:23 by nlavrine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void		fill_rooms(t_rooms *begin)
{
	t_rooms *iter_room;

	iter_room = begin;
	while (iter_room)
	{
		if (iter_room->dist != UINT16_MAX)
			iter_room->dist = INT16_MAX;
		iter_room = iter_room->next;
	}
}

void		delete_sub(t_rooms *room, char *name)
{
	t_rooms	*sub;
	t_rooms *prev_sub;
	t_rooms *next_sub;

	sub = NULL;
	next_sub = NULL;
	prev_sub = NULL;
	if (room && room->sub)
	{
		sub = find_room(room->sub, name);
		if (sub)
		{
			prev_sub = sub->prev;
			next_sub = sub->next;
			if (prev_sub)
				prev_sub->next = next_sub;
			if (next_sub)
				next_sub->prev = prev_sub;
			if (sub == room->sub)
				room->sub = next_sub;
			ft_memdel((void **)&sub->name);
			ft_memdel((void **)&sub);
		}
	}
}

t_queue		*find_way_one(t_rooms *end, int ant)
{
	t_rooms *iter_prev;
	t_queue	*queue;
	int		dist;

	iter_prev = end;
	queue = NULL;
	dist = 0;
	while (iter_prev->prev_answer)
	{
		push_queue(&queue, iter_prev->name);
		queue->id = ant;
		queue->id_name = iter_prev->id;
		queue->room = iter_prev->prev_answer;
		iter_prev = iter_prev->prev_answer;
		delete_sub(iter_prev, queue->name);
		if (iter_prev->prev_answer)
		{
			iter_prev->dist = UINT16_MAX;
			iter_prev->prev_dist = ant;
		}
		dist++;
	}
	queue->dist = dist;
	return (queue);
}

void		del_node(t_mult_q *del)
{
	t_mult_q *prev;

	// recalc(mult, tmp, 1);
	prev = del->prev;
	prev->next = NULL;
	free_mult(&del);
}

t_queue		**in_queue(t_mult_q	*mult, t_queue *queue, int *i)
{
	t_mult_q	*iter_mult;
	t_queue		*q1;
	t_queue		*q2;

	iter_mult = mult;
	q1 = queue;
	*i = 0;
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
					(*i)++;
					ft_printf("q1 id = %i q2 id %i name = %s\n",
					q1->id, q2->id, q1->name);
				}
				q1 = q1->next;
			}
			q2 = q2->next;
		}
		if (*i)
			return (&iter_mult->queue);
		iter_mult = iter_mult->next;
	}
	return (NULL);
}

void		find_way(t_rooms *begin, t_rooms *end, t_rooms *b_room, int ants)
{
	int			i;
	t_mult_q	*mult;
	t_mult_q	*i_mult;
	int			tmp[100];

	i = 0;
	mult = create_mult();
	i_mult = mult;
	mult->ants = ants;
	mult->iter_ants = ants;
	while (mult->iter_ants > 0)
	{
		i_mult = i && mult->recalc ? add_mult(i_mult) : i_mult;
		dijkstra(b_room);
		i_mult->queue = find_way_one(end, i);
		if (i)
		{
			mult->recalc = analyze_queue(mult, i_mult, tmp);
			if (mult->recalc)
				mult->lines = relevance(tmp, i, &mult->iter_ants, i_mult->prev);
		}
		fill_rooms(begin);
		i += mult->recalc;
	}
	// del_node(i_mult);
	recalc(mult, tmp, 1);
	// del_node(i_mult);
	sys_out_dist(tmp, i);
	sys_out_mult(mult);
	// mult->lines += 12;
	calculator(mult, end->id, tmp, i - 1);
}
