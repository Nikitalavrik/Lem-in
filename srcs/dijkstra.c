/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dijkstra.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlavrine <nlavrine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/24 10:09:43 by nlavrine          #+#    #+#             */
/*   Updated: 2019/08/28 18:18:11 by nlavrine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int			check_if_in_queue(t_queue **queue, int id_name)
{
	t_queue *iter_q;

	iter_q = *queue;
	while (iter_q)
	{
		if (iter_q->id_name == id_name)
		{
			while (iter_q && iter_q->id_name == id_name)
			{
				*queue = iter_q;
				iter_q = iter_q->next;
			}
			return (1);
		}
		iter_q = iter_q->next;
	}
	return (0);
}

int			next_queue(t_rooms *room, int id)
{
	t_rooms *iter_sub;

	iter_sub = room->sub;
	while (iter_sub)
	{
		if (iter_sub->prev_dist == id)
			return (1);
		iter_sub = iter_sub->next;
	}
	return (0);
}

int			push_room(t_queue **queue, t_rooms *iter_sub,
						t_rooms *walk, t_rooms *i_room)
{
	int	ret;

	ret = 0;
	if (walk->dist == UINT16_MAX)
	{
		if (!next_queue(walk, walk->prev_dist))
			return (ret);
		else
			ret = 1;
	}
	push_queue(queue, iter_sub->name);
	(*queue)->room = walk;
	walk->prev_answer = i_room;
	walk->dist = i_room->dist + iter_sub->path;
	return (ret);
}

int			dijkstra(t_rooms *begin_room)
{
	t_queue	*queue;
	t_rooms	*i_room;
	t_rooms	*iter_sub;
	t_rooms *walk;
	int		count;

	queue = create_queue();
	queue->room = begin_room;
	begin_room->dist = 0;
	count = 0;
	while (queue && queue->room)
	{
		i_room = queue->room;
		iter_sub = i_room->sub;
		pop_queue(&queue);
		while (iter_sub && i_room->dist != UINT16_MAX)
		{
			walk = iter_sub->sub;
			if ((walk->dist > i_room->dist + iter_sub->path || !walk->dist))
				count += push_room(&queue, iter_sub, walk, i_room);
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
		if (!mult->end)
		{
			tmp[i - 1] = mult->next->queue->dist - mult->queue->dist;
			if ((i * tmp[i - 1]) >= *ants)
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
