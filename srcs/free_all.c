/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_all.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlavrine <nlavrine@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/31 13:32:03 by nlavrine          #+#    #+#             */
/*   Updated: 2019/07/31 13:32:04 by nlavrine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void		free_room(t_rooms *begin)
{
	t_rooms *next;
	t_rooms *next_sub;

	while (begin)
	{
		next = begin->next;
		while (begin->sub)
		{
			next_sub = begin->sub->next;
			ft_memdel((void **)&begin->sub);
			begin->sub = next_sub;
		}
		ft_memdel((void **)&begin->name);
		ft_memdel((void **)&begin);
		begin = next;
	}
}

void		free_mult(t_mult_q *mult)
{
	t_mult_q *next;

	while (mult)
	{
		next = mult->next;
		free_queue(mult->queue);
		ft_memdel((void **)&mult);
		mult = next;
	}
}

void		free_queue(t_queue *queue)
{
	while (queue)
	{
		pop_queue(&queue);
	}
}
