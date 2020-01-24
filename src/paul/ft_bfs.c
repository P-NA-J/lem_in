/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bfs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pauljull <pauljull@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/07 10:18:23 by pauljull          #+#    #+#             */
/*   Updated: 2020/01/24 13:51:27 by pauljull         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/lem_in.h"

int			*ft_add_front_queue(t_queue *bfs_queue, t_room *to_add, t_room *current);
int		ft_check_line(int *line, int len, int nb);

t_room		**ft_init_bfs(t_queue *bfs_queue, t_map *galery, t_room *start)
{
	if (!(bfs_queue->queue = (t_room **)malloc(galery->nb_rooms
	* sizeof(t_room *))))
		return (NULL);
	bfs_queue->index = 0;
	if (start == galery->start)
		ft_set_bfs(galery);
	ft_add_queue(bfs_queue, start, NULL);
	return (bfs_queue->queue);
}
/*
void		ft_aug_adj_mat_line_process(t_map *galery, int **adj_mat,
									t_queue *aug_queue, t_room *current)
{
	int		j;
	int		i;

	i = current->index;
	if (((j = ft_line_check(adj_mat[i], galery->nb_rooms)) != FALSE)
	&& galery->rooms[j]->features == UNQUEUE)
		ft_add_queue(aug_queue, galery->rooms[j], current);
	else
	{
		j = 0;
		while (j < galery->nb_rooms)
		{
			if ((adj_mat[i][j] == 1) && (galery->rooms[j]->features == UNQUEUE
			|| galery->rooms[j]->features == IS_END))
				ft_add_queue(aug_queue, galery->rooms[j], current);
			j += 1;
		}
	}
}

int			*ft_adj_mat_line_process(t_map *galery, int **adj_mat,
							t_queue *bfs_q_ref, t_room *current)
{
	int		j;
	int		i;

	i = current->index;
	if (((j = ft_line_check(adj_mat[i], galery->nb_rooms)) != FALSE)
	&& galery->rooms[j]->features == UNQUEUE)
	{
		ft_add_queue(bfs_q_ref, galery->rooms[j], current);
		if (ft_augmented_bfs(galery, adj_mat, galery->rooms[j]) != NULL)
			ft_mat_mirror_change(adj_mat, 6, i, j);
		else
			adj_mat[i][j] = 5;
	}
	else
	{
		j = 0;
		while (j < galery->nb_rooms)
		{
			if (adj_mat[i][j] == UNCHANGED && galery->rooms[j]->features == IS_END)
				return (ft_add_front_queue(bfs_q_ref, galery->rooms[j], current));
			if (adj_mat[i][j] == UNCHANGED && (galery->rooms[j]->features
			== UNQUEUE || galery->rooms[j]->features == IS_END))
				ft_add_queue(bfs_q_ref, galery->rooms[j], current);
			j += 1;
		}
	}
	return (NULL);
}

int			*ft_augmented_bfs(t_map *galery, int **adj_mat, t_room *start)
{
	t_queue aug_queue;
	t_room	*current;

	if (!(aug_queue.queue = (t_room **)malloc(sizeof(t_room *)
	* galery->nb_rooms)))
		return (NULL);
	aug_queue.index = 0;
	ft_add_queue(&aug_queue, start, start->prev);
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

int			*ft_bfs(t_map *galery, int **adj_mat, t_room *start)
{
	t_queue	bfs_queue;
	t_room	*current;

	if (!(bfs_queue.queue = ft_init_bfs(&bfs_queue, galery, start)))
		return (NULL);
	while (bfs_queue.index != 0)
	{
		current = ft_remove_queue(&bfs_queue);
		if (current == galery->end)
		{
			ft_free_queue(bfs_queue, sizeof(t_queue));
			return (ft_path_builder(current, adj_mat));
		}
		if (current->features != IS_START)
			current->features = VISITED;
		if (ft_adj_mat_line_process(galery, adj_mat, &bfs_queue, current)
		!= NULL)
		{
			ft_free_queue(bfs_queue, sizeof(t_queue));
			return (ft_path_builder(galery->end, adj_mat));
		}
	}
	ft_free_queue(bfs_queue, sizeof(t_queue));
	return (NULL);
}
*/

void	ft_print_features(int features);

void	ft_adj_mat_line_process(t_map *galery, int **adj_mat,
							t_queue *bfs_q_ref, int current)
{
	int	i;

	i = -1;
	while (++i < galery->nb_rooms)
	{
		if (adj_mat[current][i] == 3 && (galery->rooms[current]->pathed == 0))
		{
			galery->rooms[i]->pathed = 1;
			ft_add_queue(bfs_q_ref, galery->rooms[i], galery->rooms[current]);
		}
		else if ((galery->rooms[current]->pathed == 1 && adj_mat[current][i] == 3) || adj_mat[current][i] == 1)
		{
			galery->rooms[current]->pathed = 0;
			if (galery->rooms[i]->features == IS_END)
			{
				ft_add_front_queue(bfs_q_ref, galery->rooms[i], galery->rooms[current]);
				return ;
			}
			if (galery->rooms[i]->features == UNQUEUE && ft_check_line(adj_mat[i], galery->nb_rooms, 4) == FALSE)
				ft_add_queue(bfs_q_ref, galery->rooms[i], galery->rooms[current]);
		}
	}
}

int			*ft_bfs(t_map *galery, int **adj_mat, t_room *start)
{
	t_queue	bfs_queue;
	t_room	*current;

	if (!(bfs_queue.queue = ft_init_bfs(&bfs_queue, galery, start)))
		return (NULL);
	while (bfs_queue.index != 0)
	{
		if ((current = ft_remove_queue(&bfs_queue)) == galery->end)
		{
			ft_free_queue(bfs_queue, sizeof(t_queue));
			return (ft_path_builder(current, adj_mat));
		}
		ft_adj_mat_line_process(galery, adj_mat, &bfs_queue, current->index);
	}
	ft_free_queue(bfs_queue, sizeof(t_queue));
	return (NULL);
}
