/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_path_builder.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pauljull <pauljull@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/10 10:01:52 by pauljull          #+#    #+#             */
/*   Updated: 2019/12/10 10:02:13 by pauljull         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

static size_t		ft_path_length(t_room *end_point)
{
	size_t	len;

	len = 0;
	if (end_point == NULL)
		return (0);
	while (end_point->features != IS_START)
	{
		len += 1;
		if (end_point->features != IS_START)
			end_point = end_point->prev;
	}
	return (len + 1);
}

int			*ft_path_builder(t_room *end_point)
{
	size_t	path_size;
	int		*path;

	path_size = ft_path_length(end_point);
	if (!(path = (int *)malloc(sizeof(int) * path_size)))
		return (NULL);
	while (path_size >= 0)
	{
		path[path_size] = end_point->index;
		path_size -= 1;
		if (end_point->features != IS_START)
			end_point = end_point->prev;
	}
}