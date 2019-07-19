/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlavrine <nlavrine@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/19 15:10:54 by nlavrine          #+#    #+#             */
/*   Updated: 2019/07/19 15:10:56 by nlavrine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IN_H
# define LEM_IN_H

# include "../libft/libft.h"
# include <stdarg.h>
# include "../libft/get_next_line.h"

int			ft_printf(const char *s, ...);

typedef struct		s_rooms
{
	char			*name;
	int				id;
	struct s_rooms	*sub;
	struct s_rooms	*next;
}					t_rooms;

t_rooms				*create_room(void);
t_rooms				*add_room(t_rooms **begin);

int					parsing(t_rooms *begin);

void				sys_out_rooms(t_rooms *begin);
void				find_add_sub(t_rooms *begin, char *line);

#endif
