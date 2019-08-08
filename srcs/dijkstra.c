/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bfs.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlavrine <nlavrine@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/24 10:09:43 by nlavrine          #+#    #+#             */
/*   Updated: 2019/07/24 10:09:48 by nlavrine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

t_rooms		*go_throught(t_rooms *begin, int steps)
{
	int			i;
	t_rooms		*iter_room;

	i = 0;
	iter_room = begin;
	if (!begin)
		return (NULL);
	while (iter_room && i < steps)
	{
		iter_room = iter_room->next;
		i++;
	}
	return (iter_room);
}

void		push_room(t_queue **queue, t_rooms *iter_sub,
						t_rooms *walk_throught, t_rooms *iter_room)
{
	push_queue(queue, iter_sub->name);
	(*queue)->room = walk_throught;
	walk_throught->prev_answer = iter_room;
	walk_throught->dist = iter_room->dist + iter_sub->path;
}

int			dijkstra(t_rooms *begin_room)
{
	t_queue	*queue;
	t_rooms	*iter_room;
	t_rooms	*iter_sub;
	t_rooms *walk_throught;

	queue = create_queue();
	queue->room = begin_room;
	begin_room->dist = 0;
	while (queue && queue->room)
	{
		iter_room = queue->room;
		iter_sub = iter_room->sub;
		pop_queue(&queue);
		while (iter_sub && iter_room->dist != UINT16_MAX)
		{
			walk_throught = iter_sub->sub;
			if ((walk_throught->dist > iter_room->dist + iter_sub->path\
			|| !walk_throught->dist) && walk_throught->dist != UINT16_MAX)
				push_room(&queue, iter_sub, walk_throught, iter_room);
			iter_sub = iter_sub->next;
		}
	}
	begin_room->prev_answer = NULL;
	return (1);
}

int			relevance(int *tmp, int i, int *ants, t_mult_q *mult)
{
	int	lines;

	lines = 0;
	if (*ants > 0)
	{
		if (mult->queue->id_name != mult->next->queue->id_name)
		{
			tmp[i - 1] = mult->next->queue->dist - mult->queue->dist;
			if ((i * tmp[i - 1]) > *ants)
			{
				tmp[i - 1] = (*ants / i) + (*ants % i ? 1 : 0);
				lines = tmp[i - 1] + mult->queue->dist - 1;
				*ants = 0;
			}
			else
				*ants -= i * tmp[i - 1];
		}
		else
		{
			tmp[i - 1] = (*ants / i) + (*ants % i ? 1 : 0);
			lines = tmp[i - 1] + mult->queue->dist - 1;
			*ants = 0;
		}
	}
	return (lines);
}
