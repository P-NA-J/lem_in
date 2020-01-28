/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_clean.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pauljull <pauljull@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/28 09:59:33 by pauljull          #+#    #+#             */
/*   Updated: 2020/01/28 16:09:54 by pauljull         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/lem_in.h"
t_room		**ft_init_bfs(t_queue *bfs_queue, t_map *galery, t_room *start);

void	ft_rm_link(int **adj_mat, int i, int j)
{
	adj_mat[i][j] = 0;
	adj_mat[j][i] = 0;
}

int	ft_dead_end_check(int *tab, int len)
{
	int	i;
	int	tmp_i;
	int	flag;

	i = 0;
	flag = 0;
	while (i < len)
	{
		if (tab[i] != 0)
		{
			flag += 1;
			if (flag == 1)
				tmp_i = i;
		}
		i += 1;
	}
	if (flag == 1)
		return (tmp_i);
	return (FALSE);
}

void	ft_adj_mat_line_clean_process(t_map *data, int **adj_mat,
										t_queue *c_queue, t_room *current)
{
	int	i;

	i = 0;
	if (current->features != IS_START && current->features != IS_END
	&& (i = ft_dead_end_check(adj_mat[current->index], data->nb_rooms)) != FALSE)
	{
		ft_rm_link(adj_mat, current->index, i);
		ft_add_queue(c_queue, data->rooms[i], NULL, 0);
		return ;
	}
	while (i < data->nb_rooms)
	{
		if (adj_mat[current->index][i] == 1 && data->rooms[i]->features != QUEUE
			&& data->rooms[i]->features != VISITED)
			ft_add_queue(c_queue, data->rooms[i], current, 0);
		i += 1;
	}
}

int	*ft_clean(t_map *data, int **adj_mat)
{
	t_queue	c_queue;
	t_room	*current;

	if (!(c_queue.queue = ft_init_bfs(&c_queue, data, data->start)))
		return (NULL);
	while (c_queue.index != 0)
	{
		current = ft_remove_queue(&c_queue);
		ft_adj_mat_line_clean_process(data, adj_mat, &c_queue, current);
		current->features = VISITED;
	}
	ft_free_queue(c_queue, sizeof(t_queue));
	return (NULL);
}