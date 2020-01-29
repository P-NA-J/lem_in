/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bfs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pauljull <pauljull@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/07 10:18:23 by pauljull          #+#    #+#             */
/*   Updated: 2020/01/29 18:21:23 by pauljull         ###   ########.fr       */
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
/*
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
		if (adj_mat[current->index][i] == UNCHANGED)
		{
			if ((tmp = ft_check_line(adj_mat[i], data->nb_rooms, 4)) != FALSE)
			{
				continue ;
			}
			else if ((tmp = ft_check_line(adj_mat[i], data->nb_rooms, 3)) != FALSE && nb_branch == 1)
			{
				if (data->rooms[i]->time > (current->time + 1))
				{
					data->rooms[i]->time = current->time + 1;
					data->rooms[i]->prev = current;
					ft_add_queue(bfs_q_ref, data->rooms[tmp], data->rooms[i], -1);
				}
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
*/
void	ft_augmented_link_management(t_map *data, int index,
							t_queue *bfs_q_ref, t_room *current)
{
	int	nb_branch;

	printf("AUG index = %d salle [%s]\n", index, data->rooms[index]->name);
	nb_branch = ft_occurence_count(data, data->adj_mat[current->index], 1, data->nb_rooms);
	if (nb_branch == 1)
		ft_add_queue(bfs_q_ref, data->rooms[index], current, -1);
}

void	ft_unchanged_link_management(t_map *data, int index,
							t_queue *bfs_q_ref, t_room *current)
{
	int	tmp_inf;
	int	tmp_aug;
	int	nb_branch;

	nb_branch = ft_occurence_count(data, data->adj_mat[current->index], 1, data->nb_rooms);
	tmp_inf = ft_check_line(data->adj_mat[index], data->nb_rooms, INF);
	tmp_aug = ft_check_line(data->adj_mat[index], data->nb_rooms, AUGMENTED);
	if (tmp_inf != -1)
		return ;
	else if (tmp_aug == -1)
		ft_add_queue(bfs_q_ref, data->rooms[index], current, 1);
	else if (tmp_aug != -1 && nb_branch == 1)
	{
		if (data->rooms[index]->time > (current->time + 1))
		{
			data->rooms[index]->time = current->time + 1;
			data->rooms[index]->prev = current;
			ft_add_queue(bfs_q_ref, data->rooms[tmp_aug], data->rooms[index], -1);
		}
	}
}

void	ft_adj_mat_line_process(t_map *data, int **adj_mat,
							t_queue *bfs_q_ref, t_room *current)
{
	int	i;

	i = -1;
	if (adj_mat[current->index][data->end->index] == UNCHANGED)
	{
		ft_add_front_queue(bfs_q_ref, data->end, current);
		return ;
	}
	while (++i < data->nb_rooms)
	{
		if (adj_mat[current->index][i] == UNCHANGED)
			ft_unchanged_link_management(data, i, bfs_q_ref, current);
		else if (adj_mat[current->index][i] == AUGMENTED)
			ft_augmented_link_management(data, i, bfs_q_ref, current);
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
