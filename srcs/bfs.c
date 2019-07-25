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

int			dijkstra(t_rooms *begin)
{
	t_queue	*queue;
	t_rooms	*iter_room;
	t_rooms	*iter_sub;
	t_rooms *walk_throught;

	queue = create_queue();
	queue->room = begin;
	begin->dist = 0;
	while (queue && queue->room)
	{
		iter_room = queue->room;
		iter_sub = iter_room->sub;
		pop_queue(&queue);
		while (iter_sub)
		{
			walk_throught = go_throught(begin, iter_sub->id);
			if (walk_throught->dist > iter_room->dist + iter_sub->path || !walk_throught->dist)
			{
				push_queue(&queue, iter_sub->name);
				queue->room = walk_throught;
				walk_throught->prev = iter_room;
				walk_throught->dist = iter_room->dist + iter_sub->path;
			}
			iter_sub = iter_sub->next;
		}
	}
	begin->prev = NULL;
	return (1);
}
