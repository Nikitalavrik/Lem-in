/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlavrine <nlavrine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/18 19:47:14 by nlavrine          #+#    #+#             */
/*   Updated: 2019/08/29 16:39:28 by nlavrine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int		parse_options(char *param)
{
	int i;
	int	flags;

	i = 1;
	flags = 0;
	if (param[0] != '-')
		print_error("usage: ./lem-in [-loh]");
	while (param[i])
	{
		if (param[i] == 'l')
			flags |= 1;
		else if (param[i] == 'o')
			flags |= 2;
		else
			print_error("usage: ./lem-in [-loh]");
		i++;
	}
	return (flags);
}

void	check_errors(int ants, t_rooms *begin_room, t_rooms *end)
{
	if (ants <= 0)
		print_error("Parsing: bad number of ants");
	if (!begin_room)
		print_error("Parsing: please write start");
	if (!end)
		print_error("Parsing: please write end");
}

int		main(int argc, char **argv)
{
	t_rooms *begin;
	int		ants;
	t_rooms	*end;
	t_rooms	*begin_room;

	end = NULL;
	begin_room = NULL;
	begin = create_room();
	ants = 1;
	while (ants < argc)
	{
		begin->flags |= parse_options(argv[ants]);
		ants++;
	}
	ants = parsing(begin, &end, &begin_room);
	check_errors(ants, begin_room, end);
	begin->flags & 2 ? write(1, "\n", 1) : 0;
	ants = find_way(begin, end, begin_room, ants);
	if (begin->flags & 1)
		ft_printf("lines = %i\n", ants);
	free_rooms(begin);
	return (0);
}
