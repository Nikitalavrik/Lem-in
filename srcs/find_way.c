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

/*
** change direct to unuse
*/

t_queue			*find_way_one(t_rooms *end, int ant)
{
	t_rooms *iter_prev;
	t_queue	*queue;
	t_rooms	*sub;
	int		dist;

	iter_prev = end;
	queue = NULL;
	dist = 0;
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
		dist++;
	}
	queue->dist = dist;
	return (queue);
}

int			is_equal_queue(t_queue *q1, t_queue *q2)
{
	t_queue *i1;
	t_queue	*i2;

	if (!q1 || !q2)
		return (1);
	i1 = q1;
	i2 = q2;
	while (i1 && i2)
	{
		if (i1->id_name != i2->id_name)
			return (1);
		i1 = i1->next;
		i2 = i2->next;
	}
	return (i1 || i2 ? 1 : 0);
}

void		print_res(t_mult_q *queue, int end_id)
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
				ft_printf("L%i-%s ", iter_q->id + 1, iter_q->queue->name);
				used[iter_q->queue->id_name] = 1;
				ft_memdel((void **)&iter_q->queue->name);
				pop_queue(&iter_q->queue);
			}
			iter_q = iter_q->next;
		}
		if (!iter->queue)
			iter = iter->next;
		if (iter && (iter->queue || (iter->next && iter->next->queue)))
			ft_printf("\n");
	}
	ft_printf("\n");
}

/*
**	Problem with many ants
*/

int			find_way(t_rooms *begin, t_rooms *end, t_rooms *begin_room, int ants)
{
	int			i;
	t_mult_q	*mult_queue;
	t_mult_q	*iter_mult;		
	t_queue		*prev_queue;
	t_mult_q	*ants_queue;

	i = 0;
	mult_queue = create_mult();
	iter_mult = mult_queue;
	prev_queue = NULL;
	while (is_equal_queue(prev_queue, iter_mult->queue))
	{
		prev_queue = iter_mult->queue;
		if (i)
			iter_mult = add_mult(iter_mult);
		dijkstra(begin, begin_room);
		iter_mult->queue = find_way_one(end, i);
		fill_rooms(begin);
		i++;
	}
	ants_queue = iter_mult->prev;
	ants_queue->next = NULL;
	ft_memdel((void **)iter_mult);
	// sys_out_mult(mult_queue);
	ants_queue = calculator(mult_queue, ants);
	print_res(ants_queue, end->id);
	free_mult(ants_queue);
	free_mult(mult_queue);
	return (1);
}	