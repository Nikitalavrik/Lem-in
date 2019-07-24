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
	// t_queue *queue;

	// queue = create_queue();
	// // queue->id = 0;
	// // push_queue(&queue);
	// // queue->id = 1;
	// // push_queue(&queue);
	// // queue->id = 2;
	// sys_print_queue(queue);
	t_rooms *begin;
	int		sum;
	int		fd;

	sum = 0;
	fd = open("test/tst1", O_RDONLY);
	begin = create_room();
	if (parsing(begin, fd))
	{
		bfs(begin, sum);
		sys_out_rooms(begin);
	}
	else
		ft_printf("Error\n");
	return (0);
}