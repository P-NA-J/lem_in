/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bfs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pauljull <pauljull@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/07 10:18:23 by pauljull          #+#    #+#             */
/*   Updated: 2020/01/28 16:32:40 by pauljull         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/lem_in.h"

int			*ft_add_front_queue(t_queue *bfs_queue, t_room *to_add, t_room *current);
int		ft_check_line(int *line, int len, int nb);
void	ft_debug_line_adj_mat(int *line, size_t size);

t_room		**ft_init_bfs(t_queue *bfs_queue, t_map *data, t_room *start)
{
	if (!(bfs_queue->queue = (t_room **)malloc(data->nb_rooms
	* sizeof(t_room *))))
		return (NULL);
	bfs_queue->index = 0;
	if (start == data->start)
		ft_set_bfs(data);
	bfs_queue->queue[0] = start;
	bfs_queue->index += 1;
	return (bfs_queue->queue);
}
/*
void		ft_aug_adj_mat_line_process(t_map *data, int **adj_mat,
									t_queue *aug_queue, t_room *current)
{
	int		j;
	int		i;

	i = current->index;
	if (((j = ft_line_check(adj_mat[i], data->nb_rooms)) != FALSE)
	&& data->rooms[j]->features == UNQUEUE)
		ft_add_queue(aug_queue, data->rooms[j], current);
	else
	{
		j = 0;
		while (j < data->nb_rooms)
		{
			if ((adj_mat[i][j] == 1) && (data->rooms[j]->features == UNQUEUE
			|| data->rooms[j]->features == IS_END))
				ft_add_queue(aug_queue, data->rooms[j], current);
			j += 1;
		}
	}
}

int			*ft_adj_mat_line_process1(t_map *data, int **adj_mat,
							t_queue *bfs_q_ref, t_room *current)
{
	int		j;
	int		i;

	i = current->index;
	if (((j = ft_line_check(adj_mat[i], data->nb_rooms)) != FALSE)
	&& data->rooms[j]->features == UNQUEUE)
	{
		ft_add_queue(bfs_q_ref, data->rooms[j], current);
		if (ft_augmented_bfs(data, adj_mat, data->rooms[j]) != NULL)
			ft_mat_mirror_change(adj_mat, 6, i, j);
		else
			adj_mat[i][j] = 5;
	}
	else
	{
		j = 0;
		while (j < data->nb_rooms)
		{
			if (adj_mat[i][j] == UNCHANGED && data->rooms[j]->features == IS_END)
				return (ft_add_front_queue(bfs_q_ref, data->rooms[j], current));
			if (adj_mat[i][j] == UNCHANGED && (data->rooms[j]->features
			== UNQUEUE || data->rooms[j]->features == IS_END))
				ft_add_queue(bfs_q_ref, data->rooms[j], current);
			j += 1;
		}
	}
	return (NULL);
}

int			*ft_augmented_bfs(t_map *data, int **adj_mat, t_room *start)
{
	t_queue aug_queue;
	t_room	*current;

	if (!(aug_queue.queue = (t_room **)malloc(sizeof(t_room *)
	* data->nb_rooms)))
		return (NULL);
	aug_queue.index = 0;
	ft_add_queue(&aug_queue, start, start->prev);
	start->features = AUG_START;
	while (aug_queue.index != 0)
	{
		current = ft_remove_queue(&aug_queue);
		if (current == data->end)
			return (ft_get_aug_path(current, adj_mat));
		if (current->features != IS_START && current->features != AUG_START)
			current->features = AUG_VISITED;
		ft_aug_adj_mat_line_process(data, adj_mat, &aug_queue, current);
	}
	ft_aug_clean(data->rooms, data->nb_rooms);
	return (NULL);
}

int			*ft_bfs(t_map *data, int **adj_mat, t_room *start)
{
	t_queue	bfs_queue;
	t_room	*current;

	if (!(bfs_queue.queue = ft_init_bfs(&bfs_queue, data, start)))
		return (NULL);
	while (bfs_queue.index != 0)
	{
		current = ft_remove_queue(&bfs_queue);
		if (current == data->end)
		{
			ft_free_queue(bfs_queue, sizeof(t_queue));
			return (ft_path_builder(current, adj_mat));
		}
		if (current->features != IS_START)
			current->features = VISITED;
		if (ft_adj_mat_line_process(data, adj_mat, &bfs_queue, current)
		!= NULL)
		{
			ft_free_queue(bfs_queue, sizeof(t_queue));
			return (ft_path_builder(data->end, adj_mat));
		}
	}
	ft_free_queue(bfs_queue, sizeof(t_queue));
	return (NULL);
}
*/

void	ft_print_features(int features);
/*
void	ft_adj_mat_line_process2(t_map *data, int **adj_mat,
							t_queue *bfs_q_ref, int current)
{
	int	i;

	i = -1;
	while (++i < data->nb_rooms)
	{
//		printf("adj_mat[%s][%s] = %d\n", data->rooms[current]->name, data->rooms[i]->name, adj_mat[current][i]);
		if (adj_mat[current][i] == 3 && (data->rooms[current]->pathed == 0))
		{
//			printf("MAIS C'ETAIT SUR EN FAIT\n");
			data->rooms[i]->pathed = 1;
			ft_add_queue(bfs_q_ref, data->rooms[i], data->rooms[current]);
		}
		else if ((data->rooms[current]->pathed == 1 && adj_mat[current][i] == 3) || adj_mat[current][i] == 1)
		{
			data->rooms[current]->pathed = 0;
			if (data->rooms[i]->features == IS_END)
			{
				ft_add_front_queue(bfs_q_ref, data->rooms[i], data->rooms[current]);
				return ;
			}
			if (data->rooms[i]->features == UNQUEUE && ft_check_line(adj_mat[i], data->nb_rooms, 4) == FALSE)
			{
//				printf("ADDING %s\n", data->rooms[i]->name);
				ft_add_queue(bfs_q_ref, data->rooms[i], data->rooms[current]);
			}
		}
	}
}


void	ft_adj_mat_line_process3(t_map *data, int **adj_mat,
							t_queue *bfs_q_ref, t_room *current)
{
	int	tmp;
	int	i;

	i = -1;
	
	if (adj_mat[current->index][data->end->index] == 1)
	{
		ft_add_front_queue(bfs_q_ref, data->rooms[data->end->index], data->rooms[current->index]);
		return ;
	}
	if ((tmp = ft_check_line(adj_mat[current->index], data->nb_rooms, 3)) != FALSE && current->pathed == 0)
	{
		data->rooms[tmp]->pathed = 1;
		ft_add_queue(bfs_q_ref, data->rooms[tmp], data->rooms[current->index], -1);
	}
	if (data->rooms[current->index]->pathed == 0)
	{
		while (++i < data->nb_rooms)
		{
			if (adj_mat[current->index][i] == 1 && data->rooms[i]->features == UNQUEUE && (tmp = ft_check_line(adj_mat[i], data->nb_rooms, 4)) != FALSE)
				i += 1;
			if (adj_mat[current->index][i] == 1 && data->rooms[i]->features == UNQUEUE && (tmp = ft_check_line(adj_mat[i], data->nb_rooms, 3)) != FALSE)
			{
				ft_add_queue(bfs_q_ref, data->rooms[i], data->rooms[current->index], 1);
				ft_add_queue(bfs_q_ref, data->rooms[tmp], data->rooms[i], -1);
				data->rooms[tmp]->pathed = 1;
			}
			else if (adj_mat[current->index][i] == 1 && data->rooms[i]->features == UNQUEUE && (tmp = ft_check_line(adj_mat[i], data->nb_rooms, 3)) == FALSE)
				ft_add_queue(bfs_q_ref, data->rooms[i], data->rooms[current->index], 1);
		}
	}
	else
	{
		while (++i < data->nb_rooms)
		{
			if ((adj_mat[current->index][i] == 1 || adj_mat[current->index][i] == 3) && data->rooms[i]->features == UNQUEUE)
				ft_add_queue(bfs_q_ref, data->rooms[i], current, -1);
		}
	}
	
}
*/

int		ft_occurence_count(t_map *data, int *tab, int to_find, int len)
{
	int i;
	int	occurence;

	i = -1;
	occurence = 0;
	while (++i < len)
	{
		if (tab[i] == to_find && data->rooms[i]->features != QUEUE)
			occurence += 1;
	}
	return (occurence);
}

void	ft_adj_mat_line_process(t_map *data, int **adj_mat,
							t_queue *bfs_q_ref, t_room *current)
{
	int	nb_branch;
	int	i;
	int	tmp;

	i = -1;
	nb_branch = ft_occurence_count(data, adj_mat[current->index], 1, data->nb_rooms);
	if (adj_mat[current->index][data->end->index] == 1)
	{
		ft_add_front_queue(bfs_q_ref, data->end, current);
		return ;
	}
	while (++i < data->nb_rooms)
	{
		if (adj_mat[current->index][i] == 1)
		{
			if ((tmp = ft_check_line(adj_mat[i], data->nb_rooms, 4)) != FALSE)
			{
				continue ;
			}
			else if ((tmp = ft_check_line(adj_mat[i], data->nb_rooms, 3)) != FALSE && nb_branch == 1)
			{
				data->rooms[i]->time = current->time + 1;
				data->rooms[i]->prev = current;
				ft_add_queue(bfs_q_ref, data->rooms[tmp], data->rooms[i], -1);
			}
			else if (ft_line_check(adj_mat[i], data->nb_rooms) == -1)
			{
				ft_add_queue(bfs_q_ref, data->rooms[i], current, 1);
			}
		}
		if (adj_mat[current->index][i] == 3)
			if (nb_branch == 1)
				ft_add_queue(bfs_q_ref, data->rooms[i], current, -1);
	}
}

int			*ft_bfs(t_map *data, int **adj_mat, t_room *start)
{
	t_queue	bfs_queue;
	t_room	*current;

	if (!(bfs_queue.queue = ft_init_bfs(&bfs_queue, data, start)))
		return (NULL);
	while (bfs_queue.index != 0)
	{
		if ((current = ft_remove_queue(&bfs_queue)) == data->end)
		{
			ft_free_queue(bfs_queue, sizeof(t_queue));
			return (ft_path_builder(current, adj_mat));
		}
//		ft_debug_room(current, RESTRICT);
		ft_adj_mat_line_process(data, adj_mat, &bfs_queue, current);
	}
	ft_free_queue(bfs_queue, sizeof(t_queue));
	return (NULL);
}
