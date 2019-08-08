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

typedef struct		s_mult_q
{
	int				id;
	int				lines;
	int				ants;
	struct s_queue	*queue;
	struct s_mult_q	*next;
	struct s_mult_q	*prev;
}					t_mult_q;

typedef	struct		s_queue
{
	int				id;
	int				id_name;
	char			*name;
	long			dist;
	struct s_rooms	*room;
	struct s_queue	*next;
}					t_queue;


typedef struct		s_rooms
{
	char			*name;
	int				id;
	long			dist;
	long			path;
	int				x;
	int				y;
	struct s_rooms	*sub;
	struct s_rooms	*prev;
	struct s_rooms	*prev_answer;
	struct s_rooms	*next;
}					t_rooms;

int					parsing(t_rooms *begin, int fd, t_rooms **end, t_rooms **b);
int					dijkstra(t_rooms *begin_room);
int					find_way(t_rooms *begin, t_rooms *end, t_rooms *b, int ants);
int					relevance(int *tmp, int i, int *ants, t_mult_q *mult);
int					check_name_x_y(t_rooms *begin, t_rooms *room);

void				sys_out_dist(int *dist, int n);
void				sys_out_rooms(t_rooms *begin);
void				sys_out_queue(t_queue *queue);
void				sys_out_mult(t_mult_q *mult);

int					find_add_sub(t_rooms *begin, char *line);
t_rooms				*create_room(void);
t_rooms				*add_room(t_rooms **begin);
t_rooms				*find_room(t_rooms * begin, char *room_name);
t_rooms				*go_end(t_rooms *begin);
t_rooms				*go_throught(t_rooms *begin, int steps);

t_mult_q			*calculator(t_mult_q *mult, int ants, int *tmp, int len);
t_mult_q			*create_mult();
t_mult_q			*add_mult(t_mult_q *begin);
t_queue				*create_queue();
void				push_queue(t_queue **queue, char *name);
void				pop_queue(t_queue **queue);

void				free_queue(t_queue **queue);
void				free_rooms(t_rooms *begin);
void				free_mult(t_mult_q **mult);
void				free_sub(t_rooms *sub);

#endif
