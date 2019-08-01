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

int		check_name_x_y(t_rooms *begin, t_rooms *room)
{
	t_rooms	*iter;
	char	*name;
	int		x;
	int		y;

	iter = begin;
	name = room->name;
	x = room->x;
	y = room->y;
	while (iter->next)
	{
		if (!ft_strcmp(iter->name, name) || (iter->x == x && iter->y == y))
			return (0);
		iter = iter->next;
	}
	return (1);
}

int		add_name(t_rooms *begin, char *line, t_rooms *room, int id)
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
	room->x = ft_atoi(line + len);
	room->y = ft_atoi(ft_strchr(line + len, ' '));
	room->name = name;
	room->id = id;
	return (check_name_x_y(begin, room));
}

/*
**	Need to make validation
*/

int		parsing(t_rooms *begin, int fd, t_rooms **end, t_rooms **begin_room)
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

				if (!add_name(begin, line, room, id))
					return (0);
				id++;

			}
			else if (num_of_ants)
			{
				if (!find_add_sub(begin, line))
					return (0);	
			}
			num_of_ants = num_of_ants ? num_of_ants : ft_atoi(line);
		}
		if (!ft_strcmp(line, "##end"))
		{
			ft_memdel((void **)&line);
			get_next_line(fd, &line);
			room = id != 0 ? add_room(&begin) : room;
			if (!add_name(begin, line, room, id))
					return (0);
			*end = room;
			id++;
		}
		if (!ft_strcmp(line, "##start"))
		{
			ft_memdel((void **)&line);
			get_next_line(fd, &line);
			room = id != 0 ? add_room(&begin) : room;
			if (!add_name(begin, line, room, id))
					return (0);
			*begin_room = room;
			id++;
		}
		ft_memdel((void **)&line);
	}
	ft_memdel((void **)&line);
	ft_printf("num of ants = %i\n", num_of_ants);
	return (num_of_ants);
}
