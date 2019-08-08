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

void		free_rooms(t_rooms *begin)
{
	t_rooms *next;

	while (begin)
	{
		next = begin->next;
		free_sub(begin->sub);
		ft_memdel((void **)&begin->name);
		ft_memdel((void **)&begin);
		begin = next;
	}
}

void		free_sub(t_rooms *sub)
{
	t_rooms *next_sub;

	while (sub)
	{
		next_sub = sub->next;
		ft_memdel((void **)&sub->name);
		ft_memdel((void **)&sub);
		sub = next_sub;
	}
}

void		free_mult(t_mult_q **mult)
{
	t_mult_q	*next;

	while (*mult)
	{
		next = (*mult)->next;
		free_queue(&(*mult)->queue);
		(*mult)->next = NULL;
		(*mult)->prev = NULL;
		ft_memdel((void **)mult);
		(*mult) = next;
	}
}

void		free_queue(t_queue **queue)
{
	while (*queue)
	{
		pop_queue(queue);
	}
}
