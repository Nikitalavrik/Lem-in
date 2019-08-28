/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_way.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlavrine <nlavrine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/25 09:48:28 by nlavrine          #+#    #+#             */
/*   Updated: 2019/08/28 19:41:12 by nlavrine         ###   ########.fr       */
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
	while (iter_prev && iter_prev->prev_answer)
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
	if (queue)
		queue->dist = dist;
	return (queue);
}

int			iterate_ways(t_mult_q *mult, t_mult_q *i_mult, int *i, int *tmp)
{
	if (!i_mult->queue)
		print_error("Solving: no way found");
	if (*i)
	{
		if (i_mult->queue->id_name == mult->id_name)
		{
			(*i)++;
			return (0);
		}
		mult->id_name = i_mult->queue->id_name;
		mult->recalc = analyze_queue(mult, i_mult, tmp);
		if (mult->recalc)
			mult->lines = relevance(tmp, *i, &mult->iter_ants, i_mult->prev);
	}
	return (1);
}

int			find_way(t_rooms *begin, t_rooms *end, t_rooms *b_room, int ants)
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
		if (!iterate_ways(mult, i_mult, &i, tmp))
			break ;
		fill_rooms(begin);
		i += mult->recalc;
	}
	sort_mult(mult);
	recalc(mult, tmp, 1);
	return (calculator(mult, end->id, tmp, i - 1));
}
