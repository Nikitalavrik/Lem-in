/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlavrine <nlavrine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/19 15:09:51 by nlavrine          #+#    #+#             */
/*   Updated: 2019/08/28 19:05:47 by nlavrine         ###   ########.fr       */
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
	int		len;
	char	**splited;

	len = ft_get_index(line, '-');
	if (len || line[0] <= 32)
		print_error("Parsing error: bad room name");
	splited = ft_strsplit(line, ' ');
	if (ft_splitlen(splited) != 3)
		print_error("Parsing error: bad room name");
	if (!only_digit(splited[1]) || !only_digit(splited[2]))
		print_error("Parsing error: not digits in coords");
	room->name = ft_strdup(splited[0]);
	room->x = ft_atoi(splited[1]);
	room->y = ft_atoi(splited[2]);
	room->id = id;
	clear_split(splited);
	if (!check_name_x_y(begin, room))
		print_error("Parsing error: room with same name or coords");
	return (1);
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
	else if (line[0] != '#' && ft_get_index(line, '-'))
		option = 3;
	else if (ft_strncmp(line, "#", 1))
		option = 4;
	return (option);
}

int		parsing(t_rooms *begin, t_rooms **end, t_rooms **begin_room)
{
	char	*line;
	int		ants;
	t_rooms *room;
	int		id;

	room = init_parse_data(&line, &ants, &id, begin);
	while (get_next_line(0, &line) > 0 && line && line[0] && line[0] != '\n')
	{
		begin->flags & 2 ? ft_putendl(line) : 0;
		begin->opt = choose_room(line);
		if_end_start(begin, &line, *begin_room, *end);
		if ((begin->opt == 4 || begin->opt == 2 || begin->opt == 1) && ants)
			add_to_room(&room, begin, line, &id);
		if (begin->opt == 3)
			begin->name ? find_add_sub(begin, line) :\
			print_error("Parsing error: please setup rooms");
		*begin_room = begin->opt == 1 ? room : *begin_room;
		*end = begin->opt == 2 ? room : *end;
		ft_memdel((void **)&line);
	}
	ft_memdel((void **)&line);
	if (get_next_line(0, &line) > 0)
		print_error("Parsing error: newline before block");
	ft_memdel((void **)&line);
	return (ants);
}
