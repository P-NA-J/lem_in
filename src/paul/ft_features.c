/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_features.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pauljull <pauljull@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/20 15:16:30 by pauljull          #+#    #+#             */
/*   Updated: 2020/01/08 12:23:12 by pauljull         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/lem_in.h"

int		*ft_get_aug_path(t_room *end_point, int **adj_mat)
{
	while (end_point->features != AUG_START)
	{
		end_point->features = UNQUEUE;
		if (adj_mat[end_point->index][end_point->prev->index] == 3
		|| adj_mat[end_point->index][end_point->prev->index] == 5)
		{
			adj_mat[end_point->index][end_point->prev->index] = 6;
			adj_mat[end_point->prev->index][end_point->index] = 6;
		}
		end_point = end_point->prev;
	}
	end_point->features = VISITED;
	return ((int *)1);
}

void	ft_aug_clean(t_room **rooms, int len)
{
	int	i;

	i = 0;
	while (i < len)
	{
		if (rooms[i]->features == AUG_VISITED)
			rooms[i]->features = UNQUEUE;
		i += 1;
	}
}

void	ft_set_bfs(t_map *galery)
{
	int	i;

	i = 0;
	galery->start->features = IS_START;
	galery->end->features = IS_END;
	while (i < galery->nb_rooms)
	{
		if (galery->rooms[i]->features != IS_START
		&& galery->rooms[i]->features != IS_END)
			galery->rooms[i]->features = UNQUEUE;
		i += 1;
	}
}
