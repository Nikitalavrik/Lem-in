/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlavrine <nlavrine@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/19 15:09:51 by nlavrine          #+#    #+#             */
/*   Updated: 2019/07/19 15:09:52 by nlavrine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int		add_name(char *line, t_rooms *room, int id)
{
	char	*name;
	int		len;

	len = ft_get_index(line, '-');
	if (len)
		return (0);
	len = ft_get_index(line, ' ');
	name = ft_memalloc(sizeof(char) * len);
	name = ft_strncpy(name, line, len - 1);
	name[len - 1] = '\0';
	room->name = name;
	room->id = id;
	return (1);
}

/*
**	Need to make validation
*/

int		parsing(t_rooms *begin, int fd)
{
	char	*line;
	int		num_of_ants;
	t_rooms *room;
	int		id;

	line = NULL;
	num_of_ants = 0;
	id = 0;
	room = begin;
	while (get_next_line(fd, &line) && line[0] != '\n')
	{
		if (ft_strncmp(line, "#", 1))
		{
			if (!ft_get_index(line, '-') && num_of_ants)
			{
				room = id != 0 ? add_room(&begin) : room;
				if (!add_name(line, room, id))
					return (0);
				id++;
			}
			else if (num_of_ants)
			{
				find_add_sub(begin, line);	
			}
			num_of_ants = num_of_ants ? num_of_ants : ft_atoi(line);
		}
		ft_memdel((void **)&line);
	}

	ft_printf("num of ants = %i\n", num_of_ants);
	// sys_out_rooms(begin);
	return (num_of_ants);
}
