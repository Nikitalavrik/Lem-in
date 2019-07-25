/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   queue.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlavrine <nlavrine@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/24 14:15:27 by nlavrine          #+#    #+#             */
/*   Updated: 2019/07/24 14:15:28 by nlavrine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

t_queue		*create_queue()
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
		free(del);
	}
}
