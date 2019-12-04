/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dijkstra.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pauljull <pauljull@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/28 11:22:23 by pauljull          #+#    #+#             */
/*   Updated: 2019/12/03 21:31:41 by pauljull         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

# define VISITED -1
# define QUEUE 1
# define UNCHANGED 0

t_path	*ft_bfs(t_map *galery)
{
	t_room	*bfs_queue;
	t_room	*current;
	int i;
	t_room	*tmp;

	i = 0;
	bfs_queue = malloc(galery->nb_rooms);
	ft_add_queue(&bfs_queue, galery->start);
	while (bfs_queue[0] != EMPTY)
	{
		current = ft_remove_queue(&bfs_queue);
		current->features = VISITED;
		if (current == galery->end)
			return (ft_path_builder(current));
		while ((tmp = galery->neighbors[i]) != NULL)
		{
			if (tmp->features == UNCHANGED)
			{
				tmp->prev = current;
				ft_add_queue(&bfs_queue, tmp);
			}
			tmp->features = QUEUE;
			tmp = tmp->next;
		}
		i += 1;
	}
}