/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlavrine <nlavrine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/19 15:09:51 by nlavrine          #+#    #+#             */
/*   Updated: 2019/08/08 19:36:00 by nlavrine         ###   ########.fr       */
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

int		add_to_room(t_rooms **room, t_rooms *begin, char *line, int *id)
{
	*room = *id != 0 ? add_room(&begin) : *room;
	if (!add_name(begin, line, *room, *id))
		return (0);
	(*id)++;
	return (1);
}

int		choose_room(char *line)
{
	int	option;

	option = 0;
	if (!ft_strcmp(line, "##start"))
		option = 1;
	else if (!ft_strcmp(line, "##end"))
		option = 2;
	else if (ft_get_index(line, '-'))
		option = 3;
	else if (ft_strncmp(line, "#", 1))
		option = 4;
	return (option);
}

int		parsing(t_rooms *begin, int fd, t_rooms **end, t_rooms **begin_room)
{
	char	*line;
	int		ants;
	t_rooms *room;
	int		id;
	int		opt;

	room = init_parse_data(&line, &ants, &id, begin);
	while (get_next_line(fd, &line) && line[0] != '\n')
	{
		opt = choose_room(line);
		if_end_start(opt, &line, fd);
		if ((opt == 4 || opt == 2 || opt == 1) && ants)
			if (!add_to_room(&room, begin, line, &id))
				return (0);
		if (opt == 3 && !find_add_sub(begin, line))
			return (0);
		*begin_room = opt == 1 ? room : *begin_room;
		*end = opt == 2 ? room : *end;
		ants = ants ? ants : ft_atoi(line);
		ft_memdel((void **)&line);
	}
	ft_memdel((void **)&line);
	return (ants);
}
