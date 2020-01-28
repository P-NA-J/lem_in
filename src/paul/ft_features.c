/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_features.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pauljull <pauljull@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/20 15:16:30 by pauljull          #+#    #+#             */
/*   Updated: 2020/01/28 12:42:30 by pauljull         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/lem_in.h"

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
