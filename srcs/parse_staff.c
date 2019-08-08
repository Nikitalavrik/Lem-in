/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_staff.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlavrine <nlavrine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/08 19:35:36 by nlavrine          #+#    #+#             */
/*   Updated: 2019/08/08 19:55:27 by nlavrine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	if_end_start(int opt, char **line, int fd)
{
	if (opt == 1 || opt == 2)
	{
		ft_memdel((void **)line);
		get_next_line(fd, line);
	}
}

t_rooms	*init_parse_data(char **line, int *ants, int *id, t_rooms *begin)
{
	*line = NULL;
	*ants = 0;
	*id = 0;
	return (begin);
}
