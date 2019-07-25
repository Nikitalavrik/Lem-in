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
	int		fd;
	int		ants;
	t_rooms	*end;

	fd = open("test/tst1000", O_RDONLY);
	// fd = 0;
	begin = create_room();
	if ((ants = parsing(begin, fd)))
	{
		end = go_end(begin);
		find_way(begin, end, ants);
	}
	else
		ft_printf("Error\n");
	return (0);
}