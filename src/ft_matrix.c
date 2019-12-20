/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_matrix.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pauljull <pauljull@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/20 15:15:19 by pauljull          #+#    #+#             */
/*   Updated: 2019/12/20 15:19:02 by pauljull         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

int	ft_line_check(int *line, int len)
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

int	ft_path_length_matrix(int **adj_mat, t_map *galery, int c_index)
{
	int	len;
	int	tmp;
	int	i;
	int	j;
	int	nb_room;

	len = 0;
	i = c_index;
	tmp = galery->start->index;
	nb_room = galery->nb_rooms;
	while (i != galery->end->index)
	{
		j = 0;
		while (j < nb_room)
		{
			if (adj_mat[i][j] == 1 && j != tmp)
			{
				len += 1;
				tmp = i;
				i = j;
				break ;
			}
			j += 1;
		}
	}
	return (len + 2);
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