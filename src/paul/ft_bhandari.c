/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bhandari.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pauljull <pauljull@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/12 09:13:18 by pauljull          #+#    #+#             */
/*   Updated: 2020/02/04 18:48:50 by pauljull         ###   ########.fr       */
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
//		printf("*****************************************************\n");
	}
	ft_clean_matrix(data, adj_mat);
	return (adj_mat);
}
