/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_path.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pauljull <pauljull@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/20 15:13:37 by pauljull          #+#    #+#             */
/*   Updated: 2020/01/21 16:20:01 by pauljull         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/lem_in.h"

int		ft_path_length(t_room *current)
{
	int	len;

	len = 0;
	while (current->features != IS_START)
	{
		len += 1;
		current = current->prev;
	}
	return (len + 1);
}

void	ft_mat_adjustment(int **adj_mat, t_room *end_point)
{
	if (end_point->prev->features != IS_START)
	{
		if (adj_mat[end_point->index][end_point->prev->index]
		== AUGMENTED)
			adj_mat[end_point->index][end_point->prev->index] = TO_CUT;
		else if (adj_mat[end_point->index][end_point->prev->index]
		== UNCHANGED)
			adj_mat[end_point->index][end_point->prev->index] = AUGMENTED;
	}
	else
		adj_mat[end_point->index][end_point->prev->index] = INF;
	if (adj_mat[end_point->prev->index][end_point->index] == BLOCKED)
		adj_mat[end_point->prev->index][end_point->index] = TO_CUT;
	else if (adj_mat[end_point->prev->index][end_point->index]
	== UNCHANGED)
		adj_mat[end_point->prev->index][end_point->index] = BLOCKED;
}

int		*ft_path_builder(t_room *end_point, int **adj_mat)
{
	int	len;
	int	*path;

	len = ft_path_length(end_point);
	if (!(path = (int *)malloc(sizeof(int) * (len + 2))))
		return (NULL);
	path[0] = len;
	path[1] = 0;
	while (len + 1 > 1)
	{
		if (end_point->prev != NULL)
			ft_mat_adjustment(adj_mat, end_point);
		path[len + 1] = end_point->index;
		if (end_point->features != IS_START && end_point->features != IS_END)
			end_point->path_occurence += 1;
		end_point = end_point->prev;
		len -= 1;
	}
	return (path);
}
