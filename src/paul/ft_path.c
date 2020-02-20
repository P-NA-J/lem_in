/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_path.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pauljull <pauljull@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/10 10:31:56 by pauljull          #+#    #+#             */
/*   Updated: 2020/02/20 19:39:09 by pauljull         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/lem_in.h"

/*
**	Fonction qui calcule la longueur d'un path.
*/

int		ft_path_length(int **adj_mat, int index, t_map *data)
{
	int	len;
	int	end_i;

	end_i = data->end->index;
	len = 1;
	while (index != end_i)
	{
		len += 1;
		index = ft_go_to_next(adj_mat, data->rooms[index], BLOCKED, BLOCKED);
	}
	return (len + 1);
}

/*
**	Fonction qui assigne l'index des fourmis à un chemin.
*/

void	ft_set_distrib_path(t_map *data, int path[2][PRIME],
							int count, int distrib)
{
	int	i;
	int	nb_room;

	nb_room = data->nb_rooms;
	i = 0;
	while (i < nb_room)
		path[1][i++] = 0;
	path[1][0] = count;
	path[1][1] = distrib;
}

/*
**	Fonction qui va inscrire la longueur et
**	l'index des salles composant le path.
*/

void	ft_create_path(t_map *data, int path[2][PRIME],
						int no_path, int index)
{
	t_opti	tmp_o;
	int		end_i;
	int		i;

	end_i = data->end->index;
	tmp_o = data->opti;
	path[0][0] = tmp_o.len_p[1][no_path];
	path[0][1] = START;
	i = 2;
	while (index != end_i)
	{
		path[0][i] = index;
		index = ft_go_to_next(data->adj_mat, data->rooms[index],
								BLOCKED, BLOCKED);
		i += 1;
	}
	path[0][i] = index;
}

/*
**	Fonction qui crée le tableau de path.
*/

void	ft_path(t_map *data)
{
	int	i;
	int	count;

	i = 1;
	data->path_tab[0][1][1] = data->opti.distrib_p[1][0];
	data->path_tab[0][1][0] = 1;
	ft_create_path(data, data->path_tab[0], 0, data->opti.index_p[1][0]);
	while (i < data->nb_path)
	{
		ft_create_path(data, data->path_tab[i], i, data->opti.index_p[1][i]);
		count = data->opti.distrib_p[1][i - 1] + data->path_tab[i - 1][1][0];
		ft_set_distrib_path(data, data->path_tab[i], count,
							data->opti.distrib_p[1][i]);
		i += 1;
	}
}
