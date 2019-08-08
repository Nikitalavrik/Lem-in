/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_way.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlavrine <nlavrine@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/25 09:48:28 by nlavrine          #+#    #+#             */
/*   Updated: 2019/07/25 09:48:29 by nlavrine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	fill_rooms(t_rooms *begin)
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

/*
** change direct to unuse
*/

t_queue			*find_way_one(t_rooms *end, int ant)
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
		if (iter_prev->prev_answer)
			delete_sub(iter_prev, iter_prev->prev_answer->name);
		iter_prev = iter_prev->prev_answer;
		delete_sub(iter_prev, queue->name);
		if (iter_prev->prev_answer)
			iter_prev->dist = UINT16_MAX;
		dist++;
	}
	queue->dist = dist;
	return (queue);
}

void		print_res(t_mult_q *queue, int end_id, int i)
{
	t_mult_q	*iter;
	int			used[UINT16_MAX];
	t_mult_q	*iter_q;

	iter = queue;
	while (iter)
	{
		iter_q = iter;
		ft_bzero(used, sizeof(used));
		while (iter_q)
		{
			if (iter_q->queue && (!used[iter_q->queue->id_name] || iter_q->queue->id_name == end_id))
			{
				write(1, "L", 1);
				ft_putnbr(iter_q->id + 1);
				write(1, "-", 1);
				ft_putstr(iter_q->queue->name);
				write(1, " ", 1);
				used[iter_q->queue->id_name] = 1;
				ft_memdel((void **)&iter_q->queue->name);
				pop_queue(&iter_q->queue);
			}
			iter_q = iter_q->next;
		}
		if (!iter->queue)
			iter = iter->next;
		if (i > 0)
			write(1, "\n", 1);
		i--;
	}
}

int			find_way(t_rooms *begin, t_rooms *end, t_rooms *begin_room, int ants)
{
	int			i;
	t_mult_q	*mult_queue;
	t_mult_q	*iter_mult;
	t_mult_q	*ants_queue;
	int			tmp[100];

	i = 0;
	mult_queue = create_mult();
	iter_mult = mult_queue;
	mult_queue->ants = ants;
	while (ants > 0)
	{
		if (i)
			iter_mult = add_mult(iter_mult);
		dijkstra(begin_room);
		iter_mult->queue = find_way_one(end, i);
		if (i)
			mult_queue->lines = relevance(tmp, i, &ants, iter_mult->prev);
		fill_rooms(begin);
		i++;
	}
	ants_queue = iter_mult->prev;
	ants_queue->next = NULL;
	free_mult(&iter_mult);
	ants_queue = calculator(mult_queue, mult_queue->ants, tmp, i - 1);
	ft_printf("lines = %i lin = %i\n", i, mult_queue->lines);
	print_res(ants_queue, end->id, mult_queue->lines);
	free_mult(&ants_queue);
	free_mult(&mult_queue);
	return (1);
}
