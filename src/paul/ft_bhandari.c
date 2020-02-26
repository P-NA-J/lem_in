/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bhandari.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pauljull <pauljull@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/12 09:13:18 by pauljull          #+#    #+#             */
/*   Updated: 2020/02/25 15:42:58 by aboitier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/lem_in.h"

/*
**	Cette fonction va ecrire sur une ligne de le deplacement
**	de toutes les fourmis de start a end.
*/

int	ft_s_to_e(t_map *data)
{
	int	i;
	int	nb_ants;
	int	end_i;

	ft_print_file(data);
	end_i = data->end->index;
	nb_ants = data->nb_ants;
	i = 1;
	while (i <= nb_ants)
	{
		ft_print_move(data, i, end_i);
		i += 1;
	}
	ft_putstr_buffer(&(data->buff), "\n", 1);
	ft_flush_buffer(&(data->buff));
	return (FALSE);
}

/*
**	Cette fonction va appeler en boucle le BFS afin de modeler le graphe.
**	Entre chaque appel, on ré-initialise l'état des salle
**	et on actualise le graphe.
*/

int	ft_bhandari(t_map *data, int **adj_mat)
{
	data->opti.res = INT_MAX;
	while (ft_bfs(data, adj_mat) != NULL)
	{
		ft_reset_matrix(data, adj_mat);
		if (ft_snapshot(data, &(data->opti), data->start) == FALSE)
			return (FALSE);
		if (ft_evaluate_snapshot(data, adj_mat, &(data->opti),
									data->nb_path) == FALSE)
			return (TRUE);
	}
	return (TRUE);
}
