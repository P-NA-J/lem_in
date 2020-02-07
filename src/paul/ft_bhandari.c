/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bhandari.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pauljull <pauljull@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/12 09:13:18 by pauljull          #+#    #+#             */
/*   Updated: 2020/02/07 18:44:31 by pauljull         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/lem_in.h"

/*
	Cette fonction va mettre a 0 tout les liens excepté celui qui relie start à end.
*/

int **ft_s_to_e(t_map *data, int **adj_mat)
{
	int	i;
	int	nb_rooms;

	nb_rooms = data->nb_rooms;
	i = 0;
	while (i < nb_rooms)
	{
		ft_bzero(adj_mat[i], sizeof(int) * nb_rooms);
		i++;
	}
	adj_mat[data->start->index][data->end->index] = 1;
	return (adj_mat);
}

/*
	Minimise le nombre de tours en diminuant le set de chemins.
*/

void	ft_minimize_path(t_map *data, int **adj_mat)
{
	int	*tmp;

	tmp = ft_memalloc(sizeof(int) * data->nb_rooms);
	ft_memcpy(tmp, adj_mat[0], sizeof(int) * data->nb_rooms);
	ft_bubble_sort(tmp, data->nb_rooms);
	
}

/*
	Cette fonction va appeler en boucle le BFS afin de modeler le graphe.
	Entre chaque appel, on ré-initialise l'état des salle et on actualise le graphe.
*/

int		**ft_bhandari(t_map *data, int **adj_mat)
{
	if (adj_mat[data->start->index][data->end->index] == UNCHANGED)
		return (ft_s_to_e(data, adj_mat));
	while (ft_bfs(data, adj_mat) != NULL)
	{
		ft_reset_matrix(data, adj_mat);
	}
	ft_clean_matrix(data, adj_mat);
	ft_minimize_path(data, adj_mat);
	return (adj_mat);
}
