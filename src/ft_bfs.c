/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bfs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pauljull <pauljull@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/07 10:18:23 by pauljull          #+#    #+#             */
/*   Updated: 2019/12/20 15:17:36 by pauljull         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

void	ft_aug_adj_mat_line_process(t_map *galery, int **adj_mat, t_queue *aug_queue, t_room *current)
{
	int	j;
	int i;

	i = current->index;
	if (((j = ft_line_check(adj_mat[i], galery->nb_rooms)) != FALSE) && galery->rooms[j]->features == UNQUEUE)
	{
		galery->rooms[j]->prev = current;
		ft_add_queue(aug_queue, galery->rooms[j]);
	}
	else
	{
		j = 0;
		while (j < galery->nb_rooms)
		{
			if ((adj_mat[i][j] == 1) && (galery->rooms[j]->features == UNQUEUE
			|| galery->rooms[j]->features == IS_END))
			{
				galery->rooms[j]->prev = current;
				ft_add_queue(aug_queue, galery->rooms[j]);
			}
			j += 1;
		}
	}
}

int	*ft_adj_mat_line_process(t_map *galery, int **adj_mat, t_queue *bfs_q_ref, t_room *current)
{
	int	j;
	int i;

	i = current->index;
	if (((j = ft_line_check(adj_mat[i], galery->nb_rooms)) != FALSE) && galery->rooms[j]->features == UNQUEUE)
	{
		galery->rooms[j]->prev = current;
		ft_add_queue(bfs_q_ref, galery->rooms[j]);
		if (ft_augmented_bfs(galery, adj_mat, galery->rooms[j]) != NULL)
		{
			adj_mat[i][j] = 6;
			adj_mat[j][i] = 6;
			return ((int *)1);
		}
		else
			adj_mat[i][j] = 5;
	}
	else
	{
		j = 0;
		while (j < galery->nb_rooms)
		{
			if (adj_mat[i][j] == UNCHANGED && (galery->rooms[j]->features == UNQUEUE
			|| galery->rooms[j]->features == IS_END))
			{
				galery->rooms[j]->prev = current;
				ft_add_queue(bfs_q_ref, galery->rooms[j]);
			}
			j += 1;
		}
	}
	return (NULL);
}

int		*ft_augmented_bfs(t_map *galery, int **adj_mat, t_room *start)
{
	t_queue aug_queue;
	t_room	*current;

	if (!(aug_queue.queue = (t_room **)malloc(sizeof(t_room *) * galery->nb_rooms)))
		return (NULL);
	aug_queue.index = 0;
	ft_add_queue(&aug_queue, start);
	start->features = AUG_START;
	while (aug_queue.index != 0)
	{
		current = ft_remove_queue(&aug_queue);
		if (current == galery->end)
			return (ft_get_aug_path(current, adj_mat));
		if (current->features != IS_START && current->features != AUG_START)
			current->features = AUG_VISITED;
		ft_aug_adj_mat_line_process(galery, adj_mat, &aug_queue, current);
	}
	ft_aug_clean(galery->rooms, galery->nb_rooms);
	return (NULL);
}

int *ft_bfs(t_map *galery, int **adj_mat, t_room *start)
{
	t_queue	bfs_queue;
	t_room	*current;

	if (!(bfs_queue.queue = (t_room **)malloc(galery->nb_rooms * sizeof(t_room *))))
		return (NULL);
	bfs_queue.index = 0;
	if (start == galery->start)
		ft_set_bfs(galery);
	ft_add_queue(&bfs_queue, start);
	while (bfs_queue.index != 0)
	{
		current = ft_remove_queue(&bfs_queue);
		if (current == galery->end)
			return (ft_path_builder(current, adj_mat));
		if (current->features != IS_START)
			current->features = VISITED;
		if (ft_adj_mat_line_process(galery, adj_mat, &bfs_queue, current) != NULL)
			return (ft_path_builder(galery->end, adj_mat));
	}
	return (NULL);
}
