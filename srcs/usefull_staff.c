/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   usefull_staff.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlavrine <nlavrine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/08 19:35:36 by nlavrine          #+#    #+#             */
/*   Updated: 2019/08/16 17:50:48 by nlavrine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	if_end_start(int opt, char **line, int fd)
{
	if (opt == 1 || opt == 2)
	{
		ft_memdel((void **)line);
		get_next_line(fd, line);
	}
}

t_rooms	*init_parse_data(char **line, int *ants, int *id, t_rooms *begin)
{
	*line = NULL;
	*ants = 0;
	*id = 0;
	return (begin);
}

int		recalc(t_mult_q *mult, int *tmp)
{
	t_mult_q	*iter_m;
	int			i;

	i = 0;
	iter_m = mult;
	ft_bzero(tmp, sizeof(tmp));
	mult->iter_ants = mult->ants;
	while (iter_m)
	{
		if (i)
			mult->lines = relevance(tmp, i, &mult->iter_ants, iter_m->prev);
		i++;
		iter_m = iter_m->next;
	}
	return (i);
}

int		is_identical_queue(t_queue *q1, t_queue *q2)
{
	t_queue *i1;
	t_queue *i2;

	if (!q1 || !q2)
		return (0);
	i1 = q1;
	i2 = q2;
	while (i1->next)
	{
		i2 = q2;
		while (i2->next)
		{
			if (i1->id_name == i2->id_name)
				return (1);
			i2 = i2->next;
		}
		i1 = i1->next;
	}
	return (0);
}

void	swap_queue_id(t_queue **q1, t_queue **q2)
{
	t_queue *i1;
	t_queue	*i2;
	int		id1;
	int		id2;

	i1 = *q1;
	i2 = *q2;
	id1 = i1->id;
	id2 = i2->id;
	while (i1)
	{
		i1->id = id2;
		i1 = i1->next;
	}
	while (i2)
	{
		i2->id = id1;
		i2 = i2->next;
	}
}
