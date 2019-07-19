/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlavrine <nlavrine@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/30 18:28:07 by nlavrine          #+#    #+#             */
/*   Updated: 2018/10/30 18:28:08 by nlavrine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_realloc(void *ptr, size_t prev_size, size_t new_size)
{
	char	*ret;

	if (!ptr)
		return (NULL);
	if (prev_size < new_size)
	{
		ret = ft_memcpy(ft_memalloc(new_size), ptr, prev_size);
		ft_memdel(&ptr);
		return (ret);
	}
	return (ptr);
}
