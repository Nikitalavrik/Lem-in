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

// void		free_room(t_rooms *room)
// {

// }

void		free_queue(t_queue *queue)
{
	while (queue)
	{
		if (queue->name)
			free(queue->name);
		pop_queue(&queue);
	}
}
