/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bfs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pauljull <pauljull@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/07 10:18:23 by pauljull          #+#    #+#             */
/*   Updated: 2019/12/14 21:09:07 by pauljull         ###   ########.fr       */
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
		//printf("I\n");
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
		printf("[[ %s ]]\n", current->name);
		len += 1;
		current = current->prev;
		if (len == 15)
			exit(0);
	}
	return (len + 1);
}

int	*ft_path_builder(t_room *end_point, int **adj_mat, int is_augmented)
{
	int		len;
	int		*path;

	len = ft_path_length(end_point);
	printf("len = %d\n", len);
	if (!(path = (int *)malloc(sizeof(int) * (len + 1))))
		return (0);
	path[0] = (is_augmented == 1 ? -1 : len);
	while (len > 0)
	{
		//printf("G\n");
		if (end_point->features != IS_START)
		{
			if (end_point->prev->features != IS_START)
				adj_mat[end_point->index][end_point->prev->index] = AUGMENTED;
			else
				adj_mat[end_point->index][end_point->prev->index] = INF;
			adj_mat[end_point->prev->index][end_point->index] = BLOCKED;
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

static int	ft_line_check(int *line, int n, int len)
{
	int	i;

	i = 0;
	while (i < len)
	{
		//printf("C\n");
		if (line[i] == n)
			return (i);
		i += 1;
	}
	return (0);
}

void	ft_adj_mat_line_process(t_map *galery, int **adj_mat, t_queue *bfs_q_ref, t_room *current)
{
	int	j;
	int i;

	i = current->index;
	if (((j = ft_line_check(adj_mat[i], AUGMENTED, galery->nb_rooms)) != FALSE) && galery->rooms[j]->features == UNQUEUE)
	{
		galery->rooms[j]->prev = current;
//		ft_add_queue(bfs_q_ref, galery->rooms[j]);
		if (ft_bfs(galery, adj_mat, galery->rooms[j]) != NULL)
		{
			adj_mat[i][j] = 6;
			adj_mat[j][i] = 6;
			printf("######################################## Je CUT un lien\n");
			print_info(galery);
		}
	}
	else
	{
		j = 0;
		while (j < galery->nb_rooms)
		{
			//printf("B\n");
			if (adj_mat[i][j] == UNCHANGED && (galery->rooms[j]->features == UNQUEUE
			|| galery->rooms[j]->features == IS_END))
			{
				galery->rooms[j]->prev = current;
				printf("[[ %s ]] --> ", current->name);
				fflush(stdout);
				printf("ADD QUEUE [[ %s ]]\n", galery->rooms[j]->name);
				ft_add_queue(bfs_q_ref, galery->rooms[j]);
			}
			j += 1;
		}
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
		//printf("F\n");
		while (j < galery->nb_rooms)
		{
			//printf("E\n");
			if (adj_mat[i][j] == 6)
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
		//printf("D\n");
		if (galery->rooms[i]->features != IS_START && galery->rooms[i]->features != IS_END)
			galery->rooms[i]->features = UNQUEUE;
		i += 1;
	}
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
	printf("features avant : %d\n", start->features);
	ft_add_queue(&bfs_queue, start);
	printf("features apres : %d\n", start->features);
	while (bfs_queue.index != 0)
	{
		//printf("A\n");
		current = ft_remove_queue(&bfs_queue);
		if (current == galery->end)
		{
//			print_info(galery);
			return (ft_path_builder(current, adj_mat, galery->is_augmented));
		}
		if (current->features != IS_START)
			current->features = VISITED;
		ft_adj_mat_line_process(galery, adj_mat, &bfs_queue, current);
//		ft_debug_queue(bfs_queue, bfs_queue.index);
	}
	return (NULL);
}
