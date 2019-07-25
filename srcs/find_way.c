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

int			find_way(t_rooms *end)
{
	t_rooms *iter_prev;
	t_queue	*queue;
	t_rooms	*sub;

	iter_prev = end;
	while (iter_prev)
	{
		// ft_printf("name = %s\n", iter_prev->name);
		push_queue(&queue, iter_prev->name);
		iter_prev = iter_prev->prev;
		if (iter_prev && iter_prev->sub)
		{
			// ft_printf("iter_prev %s", iter_prev->name);
			sub = find_room(iter_prev->sub, queue->name);
			sub->path = UINT16_MAX;
			// ft_printf("sub name %s\n", sub->name);
		}
	}
	sys_print_queue(queue);
	while (queue && queue->next)
	{
		ft_printf("L%s-", queue->name);
		pop_queue(&queue);
		ft_printf("%s\n", queue->name);
	}
	return (1);
}