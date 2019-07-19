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
		ft_printf("name = |%s| id |%i|\n", tmp->name, tmp->id);
		tmp_sub = tmp->sub;
		while (tmp_sub)
		{
			ft_printf("sub name = |%s| id |%i|\n", tmp_sub->name, tmp_sub->id);
		}
		ft_printf("------------------\n");
		tmp = tmp->next;
	}
}
