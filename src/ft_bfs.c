/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bfs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pauljull <pauljull@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/07 10:18:23 by pauljull          #+#    #+#             */
/*   Updated: 2019/12/16 13:15:42 by pauljull         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

void	ft_debug_room(t_room *room, int mode);
void	ft_debug_queue(t_queue bfs_queue, int mode);
void	ft_debug_rooms(t_room **rooms, size_t size, int mode);
int		*ft_augmented_bfs(t_map *galery, int **adj_mat, t_room *start);

static void	ft_slide(t_queue *bfs_queue)
{
	size_t	index;

	index = 1;
	while (index < bfs_queue->index)
	{
		bfs_queue->queue[index - 1] = bfs_queue->queue[index];
		index +=1;
	}
}

static	t_room *ft_remove_queue(t_queue *bfs_queue)
{
	t_room	*unqueue;

	unqueue = bfs_queue->queue[0];
	ft_slide(bfs_queue);
	bfs_queue->index -= 1;
	return (unqueue);
}

size_t	ft_path_length(t_room *current)
{
	size_t	len;

	len = 0;
	while (current->features != IS_START)
	{
		len += 1;
		current = current->prev;
	}
	return (len + 1);
}

int	*ft_path_builder(t_room *end_point, int **adj_mat)
{
	int		len;
	int		*path;

	len = ft_path_length(end_point);
	if (!(path = (int *)malloc(sizeof(int) * (len + 1))))
		return (NULL);
	path[0] = len;
	while (len > 0)
	{
		if (end_point->prev != NULL)
		{
			if (end_point->prev->features != IS_START)
			{
				if (adj_mat[end_point->index][end_point->prev->index] == AUGMENTED)
					adj_mat[end_point->index][end_point->prev->index] = 6;
				else if (adj_mat[end_point->index][end_point->prev->index] == UNCHANGED)
					adj_mat[end_point->index][end_point->prev->index] = 3;
			}
			else
				adj_mat[end_point->index][end_point->prev->index] = INF;
			if (adj_mat[end_point->prev->index][end_point->index] == BLOCKED)
				adj_mat[end_point->prev->index][end_point->index] = 6;
			else if (adj_mat[end_point->prev->index][end_point->index] == UNCHANGED)
				adj_mat[end_point->prev->index][end_point->index] = BLOCKED;
		}
		path[len] = end_point->index;
		if (end_point->features != IS_START && end_point->features != IS_END)
			end_point->path_occurence += 1;
		end_point = end_point->prev;
		len -= 1;
	}
	return (path);
}

static void ft_add_queue(t_queue *bfs_queue, t_room *to_add)
{
	bfs_queue->queue[bfs_queue->index] = to_add;
	bfs_queue->index += 1;
	if (to_add->features != IS_START && to_add->features != IS_END)
		to_add->features = QUEUE;
}

static int	ft_line_check(int *line, int len)
{
	int	i;

	i = 0;
	while (i < len)
	{
		if (line[i] == 3 || line[i] == 6)
			return (i);
		i += 1;
	}
	return (0);
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

void	ft_reset_matrix(t_map *galery)
{
	int	i;
	int	j;
	int	**adj_mat;

	i = 0;
	j = 0;
	adj_mat = galery->adj_mat;
	while (i < galery->nb_rooms)
	{
		j = 0;
		while (j < galery->nb_rooms)
		{
			if (adj_mat[i][j] == 6 || adj_mat[i][j] == 1)
			{
				adj_mat[i][j] = 0;
				adj_mat[j][i] = 0;
			}
			else if (adj_mat[i][j] == 4 || adj_mat[i][j] == 5 || adj_mat[i][j] == 3)
				adj_mat[i][j] = 1;
			j += 1;
		}
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
		if (galery->rooms[i]->features != IS_START && galery->rooms[i]->features != IS_END)
			galery->rooms[i]->features = UNQUEUE;
		i += 1;
	}
}

int		*ft_get_aug_path(t_room *end_point, int **adj_mat)
{
	while (end_point->features != AUG_START)
	{
			end_point->features = UNQUEUE;
		if (adj_mat[end_point->index][end_point->prev->index] == 3 || adj_mat[end_point->index][end_point->prev->index] == 5)
		{
			adj_mat[end_point->index][end_point->prev->index] = 6;
			adj_mat[end_point->prev->index][end_point->index] = 6;
		}
		end_point = end_point->prev;
	}
	end_point->features = VISITED;
	return ((int *)1);
}

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

// Je suis pas sur pour le traitement du fail du malloc, a voir avec Alban.

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
//		ft_debug_room(current, RESTRICT);
		if (current == galery->end)
			return (ft_path_builder(current, adj_mat));
		if (current->features != IS_START)
			current->features = VISITED;
		if (ft_adj_mat_line_process(galery, adj_mat, &bfs_queue, current) != NULL)
			return (ft_path_builder(galery->end, adj_mat));
	}
	return (NULL);
}
