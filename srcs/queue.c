/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   queue.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlavrine <nlavrine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/24 14:15:27 by nlavrine          #+#    #+#             */
/*   Updated: 2019/08/17 14:38:09 by nlavrine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

t_queue		*create_queue(void)
{
	t_queue	*queue;

	queue = ft_memalloc(sizeof(t_queue));
	queue->id = 0;
	queue->next = NULL;
	queue->room = NULL;
	return (queue);
}

void		push_queue(t_queue **queue, char *name)
{
	t_queue	*front;

	front = create_queue();
	front->next = (*queue);
	if (*queue)
		(*queue)->prev = front;
	front->name = name;
	(*queue) = front;
}

void		pop_queue(t_queue **queue)
{
	t_queue	*del;

	del = (*queue);
	if (del)
	{
		(*queue) = (*queue)->next;
		ft_memdel((void **)&del);
	}
}

t_mult_q	*create_mult(void)
{
	t_mult_q	*mult_queue;

	mult_queue = ft_memalloc(sizeof(t_mult_q));
	mult_queue->recalc = 1;
	return (mult_queue);
}

t_mult_q	*add_mult(t_mult_q *begin)
{
	t_mult_q	*iter_mult;
	t_mult_q	*new_mult;

	if (!begin)
		return (create_mult());
	iter_mult = begin;
	new_mult = create_mult();
	while (iter_mult->next)
	{
		iter_mult = iter_mult->next;
	}
	iter_mult->next = new_mult;
	new_mult->prev = iter_mult;
	return (new_mult);
}
