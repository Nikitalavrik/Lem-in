/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlavrine <nlavrine@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/18 19:47:14 by nlavrine          #+#    #+#             */
/*   Updated: 2019/07/18 19:47:14 by nlavrine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int		main(void)
{
	t_rooms *begin;
	int		sum;
	int		fd;
	t_rooms	*end;

	sum = 0;
	fd = open("test/tst1", O_RDONLY);
	begin = create_room();
	if (parsing(begin, fd))
	{
		dijkstra(begin, sum);
		sys_out_rooms(begin);
		end = go_end(begin);
		find_way(end);
		dijkstra(begin, sum);
		sys_out_rooms(begin);
		find_way(end);
	}
	else
		ft_printf("Error\n");
	return (0);
}