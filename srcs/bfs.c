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

t_rooms	*go_throught(t_rooms *begin, int steps)
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

int			dijkstra(t_rooms *begin, int sum)
{
	int		used[100];
	t_queue	*queue;
	t_rooms	*iter_room;
	t_rooms	*iter_sub;
	t_rooms *walk_throught;

	sum = 0;
	queue = create_queue();
	ft_bzero(used, sizeof(used));
	used[begin->id] = 1;
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
			if (!used[iter_sub->id])
			{
				used[iter_sub->id] = 1;
				push_queue(&queue, iter_sub->name);
				queue->room = walk_throught;
			}
			// ft_printf("room %s sub name %s path = %i\n", iter_room->name, iter_sub->name, iter_sub->path);
			// ft_printf("room dist %i + dist %i\n", walk_throught->dist, iter_room->dist + iter_sub->path);
			if (walk_throught->dist > iter_room->dist + iter_sub->path || !walk_throught->dist)
			{
				if (walk_throught->dist)
					walk_throught->prev = iter_room;
				walk_throught->dist = iter_room->dist + iter_sub->path;
			}
			iter_sub = iter_sub->next;
		}
	}
	return (1);
}
