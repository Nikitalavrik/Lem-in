/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rooms.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlavrine <nlavrine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/19 15:09:59 by nlavrine          #+#    #+#             */
/*   Updated: 2019/08/28 19:23:43 by nlavrine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

t_rooms		*create_room(void)
{
	t_rooms *room;

	room = ft_memalloc(sizeof(t_rooms));
	room->dist = INT16_MAX;
	room->path = 1;
	return (room);
}

t_rooms		*add_room(t_rooms **begin)
{
	t_rooms	*new_room;
	t_rooms *tmp;

	tmp = *begin;
	new_room = create_room();
	if (!tmp)
	{
		*begin = new_room;
		return (new_room);
	}
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new_room;
	new_room->prev = tmp;
	return (new_room);
}

t_rooms		*find_room(t_rooms *begin, char *room_name)
{
	t_rooms *tmp;

	tmp = begin;
	while (tmp)
	{
		if (!ft_strcmp(tmp->name, room_name))
			return (tmp);
		tmp = tmp->next;
	}
	return (NULL);
}

void		clear_split(char **splited)
{
	int	i;

	i = 0;
	while (splited[i])
	{
		ft_memdel((void **)&splited[i]);
		i++;
	}
	ft_memdel((void **)&splited);
}

int			find_add_sub(t_rooms *begin, char *line)
{
	t_rooms	*sub_room;
	t_rooms	*room;
	t_rooms	*room_sub_r;
	char	**splited;

	splited = ft_strsplit((const char *)line, '-');
	check_split_len(splited);
	if (!(room = find_room(begin, splited[0])) || !check_splited(line))
		print_error("Linking error: wrong room name");
	sub_room = add_room(&room->sub);
	if (!(room_sub_r = find_room(begin, splited[1])) || room == room_sub_r)
		print_error("Linking error: wrong room name");
	sub_room->id = room_sub_r->id;
	sub_room->name = ft_strdup(splited[1]);
	sub_room->x = room_sub_r->x;
	sub_room->y = room_sub_r->y;
	sub_room->sub = room_sub_r;
	if (!check_name_x_y(room->sub, sub_room))
		print_error("Linking error: room with same name or coords");
	sub_room = add_room(&room_sub_r->sub);
	sub_room->id = room->id;
	sub_room->name = ft_strdup(splited[0]);
	sub_room->sub = room;
	clear_split(splited);
	return (1);
}
