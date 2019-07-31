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
		// queue->dist = end->dist;
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
		// iter_room->dist
		if (iter_room)
			sub = find_room(iter_room->sub, iter_queue->name);
		if (sub)
		{
			sub->path = UINT16_MAX;
			// sub->dist += 1;
		}
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
	// q1->next = NULL;
	// free_queue(q2);
	return (0);
}

int			calc_prev_dist(int dist, int *paths, int id)
{
	int		res_dist;
	int		sum;

	res_dist = dist;
	paths[id] = dist;
	sum = 0;
	// ft_printf("id %i\n", id);
	while (id)
	{
		sum += res_dist - paths[--id];
	}
	// ft_printf("dist = %i\n", sum);
	return (sum);
}

// t_mult_q		*init_ants(t_mult_q *mult, int num_ants)
// {
// 	t_mult_q	*ants;
// 	t_mult_q	*iter_q;
// 	t_mult_q	*iter_a;
// 	int			paths[100];
// 	int			dist_sum;

// 	ants = NULL;
// 	iter_q = mult;
// 	ft_bzero(paths, sizeof(paths));
// 	while (num_ants)
// 	{
// 		iter_q = mult;
// 		while (iter_q && num_ants)
// 		{	
// 			dist_sum = calc_prev_dist(iter_q->queue->dist, paths, iter_q->queue->id);
// 			if (num_ants > dist_sum)
// 			{
// 				// ft_printf("num_ants %i dist_sum %i\n", num_ants, dist_sum);
// 				if (!ants)
// 				{
// 					ants = create_mult();
// 					iter_a = ants;
// 				}
// 				else
// 					iter_a = add_mult(iter_a);
// 				// ft_printf("ant %i queue id %i\n", num_ants, iter_q->queue->id);
// 				iter_a->id = num_ants;
// 				iter_a->queue = copy_queue(iter_q->queue);
// 				// sys_print_queue(iter_a->queue);
// 				num_ants--;
// 			}		
// 			iter_q = iter_q->next;
// 		}
// 	}
// 	return (ants);
// }

void		print_res(t_mult_q *queue, int end_id)
{
	t_mult_q	*iter;
	int			used[UINT16_MAX];
	t_mult_q	*iter_q;
	t_mult_q	*end;

	end = queue;
	// while (end->next)
	// 	end = end->next;
	// iter = end;
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
				pop_queue(&iter_q->queue);
			}
			iter_q = iter_q->next;
		}
		if (!iter->queue)
			iter = iter->next;
		if (iter && iter->queue)
			ft_printf("\n");
	}
	ft_printf("\n");
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
		dijkstra(begin);
		iter_mult->queue = find_way_one(end, i);
		// refill_rooms(iter_mult->queue, begin);
		fill_rooms(begin);
		i++;
	}
	// iter_mult = mult_queue;
	// while (iter_mult)
	// {
	// 	ft_printf("dist = %i\n", iter_mult->queue->dist);
	// 	sys_print_queue(iter_mult->queue);
	// 	iter_mult = iter_mult->next;
	// }
	// ants_queue = init_ants(mult_queue, ants);
	ants_queue = calculator(mult_queue, ants);
	print_res(ants_queue, end->id);
	// sys_print_queue(ants_queue);
	// while (ants_queue)
	// {
	// 	ft_printf("id %i\n", ants_queue->id);
	// 	sys_print_queue(ants_queue->queue);
	// 	ants_queue = ants_queue->next;
	// }
	// print_way(mult_queue);
	return (1);
}	