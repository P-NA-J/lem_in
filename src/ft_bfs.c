/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bfs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pauljull <pauljull@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/07 10:18:23 by pauljull          #+#    #+#             */
/*   Updated: 2019/12/12 18:15:35 by pauljull         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

void	ft_debug_room(t_room *room, int mode);
void	ft_debug_queue(t_queue bfs_queue, int mode);
void	ft_debug_rooms(t_room **rooms, size_t size, int mode);

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
		return (0);
	path[0] = len;
	while (len > 0)
	{
		if (end_point->features != IS_START)
		{
			if (end_point->prev->features != IS_START)
				adj_mat[end_point->prev->index][end_point->index] = AUGMENTED;
			else
				adj_mat[end_point->prev->index][end_point->index] = INF;
			adj_mat[end_point->index][end_point->prev->index] = BLOCKED;
		}
		if (end_point->features != IS_START && end_point->features != IS_END)
			end_point->features = OCCUPIED;
		path[len] = end_point->index;
		end_point = end_point->prev;
		len -= 1;
	}
	return (path);
}

static void ft_add_queue(t_queue *bfs_queue, t_room *to_add)
{
	bfs_queue->queue[bfs_queue->index] = to_add;
	bfs_queue->index += 1;
	if (to_add->features != IS_START)
		to_add->features = QUEUE;
}

void	ft_adj_mat_line_process(t_map *galery, int **adj_mat, t_queue *bfs_q_ref, t_room *current)
{
	int	j;
	int i;

	i = current->index;
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

void	ft_set_bfs(t_map *galery)
{
	int	i;

	i = 0;
	galery->start->features = IS_START;
	galery->end->features = IS_END;
	while (i < galery->nb_rooms)
	{
		if (galery->rooms[i]->features != IS_START && galery->rooms[i]->features != IS_END
		&& galery->rooms[i]->features != OCCUPIED)
			galery->rooms[i]->features = UNQUEUE;
		i += 1;
	}
}

int *ft_bfs(t_map *galery, int **adj_mat)
{
	t_queue	bfs_queue;
	t_room	*current;

	if (!(bfs_queue.queue = (t_room **)malloc(galery->nb_rooms * sizeof(t_room *))))
		return (NULL);
	bfs_queue.index = 0;
	ft_set_bfs(galery);
	ft_add_queue(&bfs_queue, galery->start);
	while (bfs_queue.index != 0)
	{
		current = ft_remove_queue(&bfs_queue);
		if (current == galery->end)
			return (ft_path_builder(current, adj_mat));
		if (current->features != IS_START)
			current->features = VISITED;
		ft_adj_mat_line_process(galery, adj_mat, &bfs_queue, current);
	}
	return (NULL);
}
