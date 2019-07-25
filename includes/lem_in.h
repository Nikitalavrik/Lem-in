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
# include <fcntl.h>

int			ft_printf(const char *s, ...);

typedef	struct		s_queue
{
	int				id;
	char			*name;
	struct s_rooms	*room;
	struct s_queue	*next;
}					t_queue;


typedef struct		s_rooms
{
	char			*name;
	int				id;
	int				dist;
	int				path;
	struct s_rooms	*sub;
	struct s_rooms	*prev;
	struct s_rooms	*next;
}					t_rooms;

t_rooms				*create_room(void);
t_rooms				*add_room(t_rooms **begin);

int					parsing(t_rooms *begin, int fd);
int					dijkstra(t_rooms *begin, int sum);
int					find_way(t_rooms *end);

void				sys_out_dist(int *dist, int n);
void				sys_out_rooms(t_rooms *begin);
void				sys_print_queue(t_queue *queue);

void				find_add_sub(t_rooms *begin, char *line);
t_rooms				*find_room(t_rooms * begin, char *room_name);
t_rooms				*go_end(t_rooms *begin);

t_queue				*create_queue();
void				push_queue(t_queue **queue, char *name);
void				pop_queue(t_queue **queue);

#endif
