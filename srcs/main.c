/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlavrine <nlavrine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/18 19:47:14 by nlavrine          #+#    #+#             */
/*   Updated: 2019/08/16 17:30:45 by nlavrine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int		main(void)
{
	t_rooms *begin;
	int		fd;
	int		ants;
	t_rooms	*end;
	t_rooms	*begin_room;

	// fd = open("test/tst5", O_RDONLY);
	fd = 0;
	end = NULL;
	begin_room = NULL;
	begin = create_room();
	ants = parsing(begin, fd, &end, &begin_room);
	if (ants > 0 && begin_room && end)
		find_way(begin, end, begin_room, ants);
	else
		ft_printf("Error\n");
	free_rooms(begin);
	return (0);
}
