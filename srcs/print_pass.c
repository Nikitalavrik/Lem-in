/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_pass.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlavrine <nlavrine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/08 19:46:28 by nlavrine          #+#    #+#             */
/*   Updated: 2019/08/08 19:47:29 by nlavrine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void		print_path(int id, char *name)
{
	write(1, "L", 1);
	ft_putnbr(id + 1);
	write(1, "-", 1);
	ft_putstr(name);
	write(1, " ", 1);
}

void		print_res(t_mult_q *queue, int end_id, int i)
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
			if (iter_q->queue &&\
			(!used[iter_q->queue->id_name] || iter_q->queue->id_name == end_id))
			{
				print_path(iter_q->id, iter_q->queue->name);
				used[iter_q->queue->id_name] = 1;
				ft_memdel((void **)&iter_q->queue->name);
				pop_queue(&iter_q->queue);
			}
			iter_q = iter_q->next;
		}
		if (!iter->queue)
			iter = iter->next;
		i-- > 0 ? write(1, "\n", 1) : 0;
	}
}
