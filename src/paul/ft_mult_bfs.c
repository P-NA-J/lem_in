/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mult_bfs.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pauljull <pauljull@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/12 09:13:18 by pauljull          #+#    #+#             */
/*   Updated: 2020/01/28 16:33:54 by pauljull         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/lem_in.h"

void	ft_debug_collission(t_map *data, int **tab_path);

int		ft_get_number_pipe(int *line, int len)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (i < len)
	{
		if (line[i] == 1)
			count += 1;
		i += 1;
	}
	return (count);
}

int		ft_get_min_pipe(t_map *data)
{
	int	min_start;
	int	min_end;

	min_start = ft_get_number_pipe(data->adj_mat[data->start->index]
	, data->nb_rooms);
	min_end = ft_get_number_pipe(data->adj_mat[data->end->index]
	, data->nb_rooms);
	return (min_start < min_end ? min_start : min_end);
}

void	ft_reset_rooms(t_room **rooms, int nb_rooms)
{
	int	i;

	i = -1;
	while (++i < nb_rooms)
	{
		rooms[i]->pathed = 0;
		rooms[i]->layer = 0;
		rooms[i]->time = 0;
	}
}

void	ft_bfs_loop(int **tab_path, t_map *data, int **adj_mat)
{
	int	i;

	i = 0;
	while ((tab_path[i] = ft_bfs(data, adj_mat, data->start))
	!= NULL)
	{
		ft_reset_rooms(data->rooms, data->nb_rooms);
		i += 1;
	}
	ft_reset_matrix(data);
	data->nb_path = i;
}

int **ft_print_exception(t_map *data)
{
	int **tab;

	if (!(tab = (int **)malloc(sizeof(int *) * 1)))
		return (NULL);
	if (!(tab[0] = (int *)malloc(sizeof(int ) * 4)))
		return (NULL);
	tab[0][0] = 2;
	tab[0][1] = 0;
	tab[0][2] = data->start->index;
	tab[0][3] = data->end->index;
	data->nb_path = 1;
	return (tab);
}

int		**ft_mult_bfs(t_map *data, int **adj_mat)
{
	int	**tab_path;
	int	min;

	ft_reset_rooms(data->rooms, data->nb_rooms);
	if (adj_mat[data->start->index][data->end->index] == 1)
	{
		tab_path = ft_print_exception(data);
		ft_distribution(tab_path, data->nb_path, data->nb_ants);
		return (tab_path);
	}
	min = ft_get_min_pipe(data);
	if (min == 0)
		return (NULL);
	if (!(tab_path = (int **)malloc(sizeof(int *) * 100)))
		return (NULL);
	ft_bfs_loop(tab_path, data, adj_mat);
	if (tab_path[0] == NULL)
		return (NULL);
	ft_bfs_loop(tab_path, data, adj_mat);
	ft_distribution(tab_path, data->nb_path, data->nb_ants);
/*	int i = 0;
	while (tab_path[i] != NULL && tab_path[i][1] != 0)
	{
		printf("[%d] ", tab_path[i][0] + tab_path[i][1] - 1);
		fflush(stdout);
		ft_debug_single_path(tab_path[i], tab_path[i][0], data);
		i += 1;
	}
	data->nb_path = i;
	ft_debug_collission(data, tab_path);
*/	return (tab_path);
}
