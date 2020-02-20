/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_initialisation.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pauljull <pauljull@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/20 15:16:30 by pauljull          #+#    #+#             */
/*   Updated: 2020/02/20 19:27:45 by pauljull         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/lem_in.h"

/*
**	Fonction qui initialise la valeur de features et de time pour chacune
**	des salles avant le début du bfs.
*/

void	ft_set_bfs(t_map *data)
{
	int	i;

	i = 0;
	data->start->features = IS_START;
	data->end->features = IS_END;
	while (i < data->nb_rooms)
	{
		if (data->rooms[i]->features != IS_START
		&& data->rooms[i]->features != IS_END)
		{
			data->rooms[i]->features = UNQUEUE;
			data->rooms[i]->time = 0;
		}
		i += 1;
	}
}

void	ft_init_bfs(t_queue *bfs_queue, t_map *data)
{
	ft_set_bfs(data);
	bfs_queue->queue[0] = data->start;
	bfs_queue->index = 1;
}
