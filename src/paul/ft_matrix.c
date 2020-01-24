/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_matrix.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pauljull <pauljull@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/20 15:15:19 by pauljull          #+#    #+#             */
/*   Updated: 2020/01/22 18:20:30 by pauljull         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/lem_in.h"

int		**ft_mat_mirror_change(int **adj_mat, int value, int i_1, int i_2)
{
	adj_mat[i_1][i_2] = value;
	adj_mat[i_2][i_1] = value;
	return (adj_mat);
}

int		ft_check_line(int *line, int len, int nb)
{
	int	i;

	i = 0;
	while (i < len)
	{
		if (line[i] == nb)
			return (TRUE);
		i += 1;
	}
	return (FALSE);
}

int		ft_line_check(int *line, int len)
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
				ft_mat_mirror_change(adj_mat, 0, i, j);
			else if (adj_mat[i][j] == 4 || adj_mat[i][j] == 5
			|| adj_mat[i][j] == 3)
				adj_mat[i][j] = 1;
			j += 1;
		}
		i += 1;
	}
}
