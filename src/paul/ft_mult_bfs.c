/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mult_bfs.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pauljull <pauljull@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/12 09:13:18 by pauljull          #+#    #+#             */
/*   Updated: 2020/01/20 17:59:52 by pauljull         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/lem_in.h"

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

int		ft_get_min_pipe(t_map *galery)
{
	int	min_start;
	int	min_end;

	min_start = ft_get_number_pipe(galery->adj_mat[galery->start->index]
	, galery->nb_rooms);
	min_end = ft_get_number_pipe(galery->adj_mat[galery->end->index]
	, galery->nb_rooms);
	return (min_start < min_end ? min_start : min_end);
}

void	ft_bfs_loop(int min, int **tab_path, t_map *galery, int **adj_mat)
{
	int	i;
	
	i = 0;
	while (i < min && (tab_path[i] = ft_bfs(galery, adj_mat, galery->start))
	!= NULL)
		i += 1;
	ft_reset_matrix(galery);
	galery->nb_path = i;
}

int		**ft_mult_bfs(t_map *galery, int **adj_mat)
{
	int	**tab_path;
	int	min;

	min = ft_get_min_pipe(galery);
	if (min == 0)
		return (NULL);
	if (!(tab_path = (int **)malloc(sizeof(int *) * min)))
		return (NULL);
	ft_bfs_loop(min, tab_path, galery, adj_mat);
	if (tab_path[0] == NULL)
		return (NULL);
	min = ft_get_min_pipe(galery);
	if (min == 0)
		return (NULL);
	ft_bfs_loop(min, tab_path, galery, adj_mat);
	ft_distribution(tab_path, galery->nb_path, galery->nb_ants);
	return (tab_path);
}
