/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_staff.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlavrine <nlavrine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/08 19:35:36 by nlavrine          #+#    #+#             */
/*   Updated: 2019/08/29 16:22:44 by nlavrine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	if_end_start(t_rooms *main, char **line, t_rooms *begin, t_rooms *end)
{
	if ((main->opt == 1 && !begin) || (main->opt == 2 && !end))
	{
		ft_memdel((void **)line);
		while (get_next_line(0, line) && (*line[0]) == '#'\
		&& ft_strncmp(*line, "##", 2))
		{
			main->flags & 2 ? ft_putendl(*line) : 0;
			ft_memdel((void **)line);
		}
		main->flags & 2 ? ft_putendl(*line) : 0;
		if (*line && ((*line[0]) <= 32))
		{
			if (main->opt == 1)
				print_error("Parsing error: something after ##start");
			else
				print_error("Paesing error: something after ##end");
		}
	}
	else if (main->opt == 1 && begin)
		print_error("Parsing error: find one more ##start");
	else if (main->opt == 2 && end)
		print_error("Parsing error: find one more ##end");
}

void	check_ants(char *line)
{
	int i;

	i = 0;
	if (!ft_strcmp(line, "##start"))
		print_error("Parsing error: start must be after number of ants");
	if (!ft_strcmp(line, "##end"))
		print_error("Parsing error: end must be after number of ants");
	if (ft_get_index(line, '-'))
		print_error("Parsing error: linking must be after number of ants");
	if (ft_get_index(line, ' '))
		print_error("Parsing error: init room must be after number of ants");
	while (line[i])
		i++;
	if (i > 10)
		print_error("Parsing error: bad number of ants");
}

t_rooms	*init_parse_data(char **line, int *ants, int *id, t_rooms *begin)
{
	*line = NULL;
	*ants = 0;
	*id = 0;
	while (get_next_line(0, line) && (*line)[0] == '#'\
								&& ft_strncmp(*line, "##", 2))
	{
		begin->flags & 2 ? ft_putendl(*line) : 0;
		ft_memdel((void **)line);
	}
	begin->flags & 2 ? ft_putendl(*line) : 0;
	check_ants(*line);
	*ants = only_digit(*line) ? ft_atoi(*line) : *ants;
	*ants <= 0 ? print_error("Parsing error: bad number of ants") : 0;
	ft_memdel((void **)line);
	*line = NULL;
	return (begin);
}

int		ft_splitlen(char **splited)
{
	int	count;

	count = 0;
	while (splited[count])
		count++;
	return (count);
}

void	check_split_len(char **splited)
{
	int		len;

	len = ft_splitlen(splited);
	if (len != 2)
		print_error("Parsing error: bad number of linking node");
}
