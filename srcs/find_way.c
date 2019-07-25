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
		iter_room->dist = INT16_MAX;
		iter_room = iter_room->next;
	}
}

void			print_way(t_mult_q *mult_queue)
{
	t_mult_q	*iter_mult;
	int			used[UINT16_MAX];

	while (mult_queue)
	{
		iter_mult = mult_queue;
		ft_bzero(used, sizeof(used));
		while (iter_mult)
		{
			if (iter_mult->queue && (!used[iter_mult->queue->id_name] || !iter_mult->queue->next))
			{
				ft_printf("L%i-%s ", iter_mult->queue->id + 1, iter_mult->queue->name);
				used[iter_mult->queue->id_name] = 1;
				pop_queue(&(iter_mult->queue));
			}
			iter_mult = iter_mult->next;
		}
		if (mult_queue->next)
			ft_printf("\n");
		if (!mult_queue->queue || !mult_queue->queue->name)
			mult_queue = mult_queue->next;
	}
}

/*
** change direct to unuse
*/

t_queue			*find_way_one(t_rooms *end, int ant)
{
	t_rooms *iter_prev;
	t_queue	*queue;
	t_rooms	*sub;

	iter_prev = end;
	queue = NULL;
	while (iter_prev->prev)
	{
		push_queue(&queue, iter_prev->name);
		queue->id = ant;
		queue->id_name = iter_prev->id;
		queue->room = iter_prev->prev;
		iter_prev = iter_prev->prev;
		if (iter_prev && iter_prev->sub)
		{
			sub = find_room(iter_prev->sub, queue->name);
			sub->path = UINT16_MAX;
		}
	}
	return (queue);
}

/*
** change direct to normal 
*/

void		refill_rooms(t_queue *queue, t_rooms *begin)
{
	t_queue	*iter_queue;
	t_rooms	*iter_room;
	t_rooms	*sub;

	iter_queue = queue;
	iter_room = begin;
	while (iter_queue && iter_queue->room)
	{
		sub = NULL;
		iter_room = iter_queue->room;
		if (iter_room)
			sub = find_room(iter_room->sub, iter_queue->name);
		if (sub)
			sub->path = 1;
		iter_queue = iter_queue->next;
	}
}

/*
**	Problem with many ants
*/

int			find_way(t_rooms *begin, t_rooms *end, int ants)
{
	int			i;
	t_mult_q	*mult_queue;
	t_mult_q	*iter_mult;		
	t_queue		*reverse_queue;

	i = 0;
	mult_queue = create_mult();
	iter_mult = mult_queue;
	reverse_queue = NULL;
	while (i < ants)
	{
		if (i % 2 && i)
			refill_rooms(reverse_queue, begin);
		if (i)
			iter_mult = add_mult(iter_mult);
		dijkstra(begin);
		iter_mult->queue = find_way_one(end, i);
		fill_rooms(begin);
		if (i % 2 == 0)
			reverse_queue = iter_mult->queue;
		i++;
	}
	print_way(mult_queue);
	return (1);
}