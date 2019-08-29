/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlavrine <nlavrine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/19 15:10:54 by nlavrine          #+#    #+#             */
/*   Updated: 2019/08/29 14:19:44 by nlavrine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IN_H
# define LEM_IN_H

# include "../libft/libft.h"
# include <stdarg.h>
# include "../libft/get_next_line.h"
# include <fcntl.h>

int					ft_printf(const char *s, ...);

typedef struct		s_mult_q
{
	int				id;
	int				lines;
	int				ants;
	int				iter_ants;
	int				recalc;
	int				end;
	int				id_name;
	struct s_queue	*queue;
	struct s_queue	*compare_q;
	struct s_mult_q	*next;
	struct s_mult_q	*prev;
}					t_mult_q;

typedef	struct		s_queue
{
	int				id;
	int				id_name;
	char			*name;
	long			dist;
	int				is_div;
	struct s_rooms	*room;
	struct s_queue	*next;
	struct s_queue	*prev;
}					t_queue;

typedef struct		s_rooms
{
	char			*name;
	int				id;
	long			dist;
	long			path;
	int				x;
	int				y;
	int				prev_dist;
	int				flags;
	int				opt;
	struct s_rooms	*sub;
	struct s_rooms	*prev;
	struct s_rooms	*prev_answer;
	struct s_rooms	*next;
}					t_rooms;

int					only_digit(char *str);
int					ft_splitlen(char **splited);
void				check_split_len(char **splited);
void				print_error(char *str);
void				if_end_start(t_rooms *main, char **line,\
										t_rooms *begin, t_rooms *end);
int					parsing(t_rooms *begin, t_rooms **end,\
										t_rooms **begin_room);
void				clear_split(char **splited);
int					check_splited(char *line);
int					check_name_x_y(t_rooms *begin, t_rooms *room);
t_rooms				*init_parse_data(char **line, int *ants, int *id,
																t_rooms *begin);

void				sort_mult(t_mult_q *mult);
int					dijkstra(t_rooms *begin_room);
int					find_way(t_rooms *begin, t_rooms *end, t_rooms *b,
																	int ants);
int					relevance(int *tmp, int i, int *ants, t_mult_q *mult);
int					analyze_queue(t_mult_q *mult, t_mult_q *last, int *tmp);
void				print_res(t_mult_q *queue, int end_id, int i);

void				sys_out_dist(int *dist, int n);
void				sys_out_rooms(t_rooms *begin);
void				sys_out_queue(t_queue *queue);
void				sys_out_mult(t_mult_q *mult);

int					find_add_sub(t_rooms *begin, char *line);
t_rooms				*create_room(void);
t_rooms				*add_room(t_rooms **begin);
t_rooms				*find_room(t_rooms *begin, char *room_name);
t_rooms				*go_throught(t_rooms *begin, int steps);

int					calculator(t_mult_q *mult, int end_id, int *tmp, int len);
int					recalc(t_mult_q *mult, int *tmp, int end);

t_mult_q			*create_mult();
t_mult_q			*add_mult(t_mult_q *begin);

t_queue				*create_queue();
void				push_queue(t_queue **queue, char *name);
void				pop_queue(t_queue **queue);
void				swap_queue_id(t_queue **q1, t_queue **q2);
int					is_identical_queue(t_queue *q1, t_queue *q2);
int					check_if_in_queue(t_queue **queue, int id_name);
t_queue				**in_queue(t_mult_q	*mult, t_queue *queue, int *overlap);
t_queue				*reshape_queue(t_queue *iter_q, int id, long *dist);

void				free_queue(t_queue **queue);
void				free_rooms(t_rooms *begin);
void				free_mult(t_mult_q **mult);
void				free_sub(t_rooms *sub);

#endif
