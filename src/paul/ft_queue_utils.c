/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_queue_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pauljull <pauljull@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/20 19:48:57 by pauljull          #+#    #+#             */
/*   Updated: 2020/02/20 21:29:43 by pauljull         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/lem_in.h"

/*
**	Echange la position de deux salle dans la queue.
*/

void	ft_swap(t_queue *bfs_queue, int i_1, int i_2)
{
	t_room *tmp;

	tmp = bfs_queue->queue[i_1];
	bfs_queue->queue[i_1] = bfs_queue->queue[i_2];
	bfs_queue->queue[i_2] = tmp;
}

/*
**	Fais remonter d'une case toutes les salles d'une queue.
*/

void	ft_slide(t_queue *bfs_queue)
{
	size_t	index;

	index = 1;
	while (index < bfs_queue->index)
	{
		bfs_queue->queue[index - 1] = bfs_queue->queue[index];
		index += 1;
	}
}

/*
**	Fais descendre d'une case toutes les salles de la queue.
*/

void	ft_slide_down(t_queue *bfs_queue)
{
	size_t	index;

	index = bfs_queue->index;
	while (index > 0)
	{
		bfs_queue->queue[index] = bfs_queue->queue[index - 1];
		index -= 1;
	}
}
