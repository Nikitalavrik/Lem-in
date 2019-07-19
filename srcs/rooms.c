/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rooms.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlavrine <nlavrine@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/19 15:09:59 by nlavrine          #+#    #+#             */
/*   Updated: 2019/07/19 15:10:01 by nlavrine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

t_rooms		*create_room(void)
{
	t_rooms *room;

	room = ft_memalloc(sizeof(t_rooms));
	room->name = NULL;;
	room->sub = NULL;
	room->next = NULL;
	room->id = 0;
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
	return (new_room);
}

t_rooms		*find_room(t_rooms * begin, char *room_name)
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

void		find_add_sub(t_rooms *begin, char *line)
{
	// t_rooms	*room;

	// room = add_room(&begin->sub);
	// room->name = ft_strdup(line);
	// room->id = 999;
	int		pos_slesh;
	char	*room_name;
	t_rooms	*sub_room;
	t_rooms	*room;
	t_rooms	*room_sub_room;
	int		len_n;

	pos_slesh = ft_get_index(line, '-');
	room_name = ft_memalloc(sizeof(char) * pos_slesh);
	room_name = ft_strncpy(room_name, line, pos_slesh - 1);
	room = find_room(begin, room_name);
	if (!room)
		return ;
	sub_room = add_room(&room->sub);
	ft_memdel((void **)&room_name); 
	len_n = ft_strlen(line);
	room_name = ft_memalloc(sizeof(char) * (len_n - pos_slesh + 1));
	room_name = ft_strncpy(room_name, line + pos_slesh, len_n - pos_slesh);
	room_sub_room = find_room(begin, room_name);
	if (!room_sub_room)
		return ;
	sub_room->id = room_sub_room->id;
	sub_room->name = room_sub_room->name;
	sub_room = add_room(&room_sub_room->sub);
	sub_room->id = room->id;
	sub_room->name = room->name;
	// ft_printf("NAME OF NODE : %s\n", )
}