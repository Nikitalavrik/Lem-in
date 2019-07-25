/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sys_output.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlavrine <nlavrine@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/19 15:12:40 by nlavrine          #+#    #+#             */
/*   Updated: 2019/07/19 15:12:41 by nlavrine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	sys_out_rooms(t_rooms *begin)
{
	t_rooms *tmp;
	t_rooms *tmp_sub;

	tmp = begin;
	while (tmp)
	{
		ft_printf("name = |%s| id = |%i| dist = |%i|\nSub : ", tmp->name, tmp->id, tmp->dist);
		tmp_sub = tmp->sub;
		while (tmp_sub)
		{
			ft_printf("|%s| ", tmp_sub->name);
			tmp_sub = tmp_sub->next;
		}
		ft_printf("\nPREV : ");
		if (tmp->prev)
			ft_printf("{%s}", tmp->prev->name);
		ft_printf("\n------------------\n");
		tmp = tmp->next;
	}

}

void	sys_out_dist(int *dist, int n)
{
	int	i;

	i = 0;
	ft_printf("DIST : ");
	while (i < n)
	{
		ft_printf("%i ", dist[i]);
		i++;
	}
	ft_printf("\n");
}

void	sys_print_queue(t_queue *queue)
{
	t_queue *iter_queue;

	iter_queue = queue;
	ft_printf("QUEUE : ");
	while (iter_queue)
	{
		ft_printf("%s ", iter_queue->name);
		iter_queue = iter_queue->next;
	}
	ft_printf("\n");
}