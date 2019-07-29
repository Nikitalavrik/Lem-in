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

t_queue	*copy_queue(t_queue *queue)
{
	t_queue	*begin;
	t_queue	*c_queue;

	begin = queue;
	while (begin)
	{
		push_queue(&c_queue, ft_strdup(begin->name));
		c_queue->id = begin->id;
		c_queue->id_name = begin->id_name;
		begin = begin->next;
	}
	return (c_queue);
}

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
		queue->dist = end->dist;
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

int			is_equal_queue(t_queue *q1, t_queue *q2)
{
	t_queue *i1;
	t_queue	*i2;

	i1 = q1;
	i2 = q2;
	if (!i1 || !i2)
		return (1);
	while (i1 && i2)
	{
		if (i1->id_name != i2->id_name)
			return (1);
		i1 = i1->next;
		i2 = i2->next;
	}
	return (0);
}

int			calc_prev_dist(int dist, int *paths, int id)
{
	int		res_dist;

	res_dist = dist;
	paths[id] = dist;
	if (!id)
		return (0);
	while (id)
	{
		res_dist -= paths[--id];
	}
	return (res_dist);
}

t_mult_q		*init_ants(t_mult_q *mult, int num_ants)
{
	t_mult_q	*ants;
	t_mult_q	*iter_q;
	t_mult_q	*iter_a;
	int			paths[100];

	ants = NULL;
	iter_q = mult;
	ft_bzero(paths, sizeof(paths));
	while (num_ants)
	{
		iter_q = mult;
		while (iter_q && num_ants)
		{	
			if (num_ants > calc_prev_dist(iter_q->queue->dist, paths, iter_q->queue->id))
			{
				if (!ants)
				{
					ants = create_mult();
					iter_a = ants;
				}
				else
					iter_a = add_mult(iter_a);
				iter_a->id = num_ants;
				iter_a->queue = copy_queue(iter_q->queue);
				num_ants--;
			}		
			iter_q = iter_q->next;
		}
	}
	return (ants);
}

void		print_res(t_mult_q *queue)
{
	t_mult_q	*iter;
	int			used[UINT16_MAX];
	t_mult_q	*iter_q;
	t_mult_q	*end;

	end = queue;
	while (end->next)
		end = end->next;
	iter = end;
	while (end->queue)
	{
		// ft_printf("ants = %i\n", iter->id);
		iter_q = iter;
		ft_bzero(used, sizeof(used));
		while (iter_q)
		{
			// ft_printf("ants = %i\n", iter_q->id);
			if (iter_q->queue && !used[iter_q->queue->id_name])
			{
				ft_printf("L%i-%s ", iter_q->id, iter_q->queue->name);
				used[iter_q->queue->id_name] = 1;
				iter_q->queue = iter->queue->next;
			}
			iter_q = iter_q->prev;
		}
		ft_printf("\n");

		// iter = iter->prev;
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
	t_queue		*prev_queue;

	i = 0;
	mult_queue = create_mult();
	iter_mult = mult_queue;
	prev_queue = NULL;
	while (is_equal_queue(prev_queue, iter_mult->queue))
	{
		prev_queue = iter_mult->queue;
		if (i)
			iter_mult = add_mult(iter_mult);
		dijkstra(begin);
		iter_mult->queue = find_way_one(end, i);
		fill_rooms(begin);
		i++;
	}
	iter_mult = mult_queue;
	while (iter_mult)
	{
		ft_printf("dist = %i\n", iter_mult->queue->dist);
		sys_print_queue(iter_mult->queue);
		iter_mult = iter_mult->next;
	}
	print_res(init_ants(mult_queue, ants));
	// print_way(mult_queue);
	return (1);
}