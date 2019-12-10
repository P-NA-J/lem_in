/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bfs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pauljull <pauljull@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/07 10:18:23 by pauljull          #+#    #+#             */
/*   Updated: 2019/12/10 09:19:48 by pauljull         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

# define VISITED -1
# define QUEUE 1
# define UNCHANGED 0
# define EMPTY -2

t_path	*ft_bfs(t_map *galery, int **adj_mat)
{
	t_room	*bfs_queue;
	t_room	*current;
	size_t	i;
	size_t	j;

	i = 0;
	if (!(bfs_queue = (t_room *)malloc(galery->nb_rooms * sizeof(t_room))))
		return (NULL);
	ft_add_queue(&bfs_queue, galery->start);
	while (bfs_queue != EMPTY)
	{
		current = ft_remove_queue(&bfs_queue);
		current->features = VISITED;
		if (current == galery->end)
			return (ft_path_builder(current));
		while (j < galery->nb_rooms)
		{
			if (adj_mat[i][j] == UNCHANGED)
			{
				galery->rooms[j]->prev = current;
				ft_add_queue(&bfs_queue, galery->rooms[j]);
			}
			galery->rooms[j]->features = QUEUE;
			j += 1;
		}
		i += 1;
	}
}
/*
t_path	*ft_bfs(t_map *galery)
{
	t_room	*bfs_queue;
	t_room	*current;
	size_t	i;
	size_t	j;

	i = 0;
	if (!(bfs_queue = (t_room *)malloc(galery->nb_rooms * sizeof(t_room))))
		return (NULL);
	ft_add_queue(&bfs_queue, galery->start);
	while (bfs_queue != EMPTY)
	{
		current = ft_remove_queue(&bfs_queue);
		current->features = VISITED;
		if (current == galery->end)
			return (ft_path_builder(current));
		while (j < galery->nb_rooms)
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
*/