/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_distribution.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pauljull <pauljull@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/12 17:32:59 by pauljull          #+#    #+#             */
/*   Updated: 2020/02/13 13:29:45 by pauljull         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/lem_in.h"

/*
	Fonction qui sauvegarde le set actuel.
*/

int	ft_save_new_set(t_map *data, int **adj_mat, t_opti *opti)
{

}

/*
	Fonction qui rétablit l'ancien meilleur set.
*/

int	ft_recover_set(t_map *data, int **adj_mat, t_opti *opti)
{

}

/*
	Fonction qui va repartir les fourmis sur les differents chemins du path.
*/

void	ft_process_set(t_opti *opti, int nb_path)
{
	
}

/*
	Fonction qui inscrit le set à examiner dans tmp_p et qui détermine si on le garde ou pas.
*/

int	ft_distribution(t_map *data, int **adj_mat, t_opti *opti)
{
	int	i;
	int	j;

	j = 0;
	i = 0;
	while (i < data->nb_rooms)
	{
		if (adj_mat[START][i] == BLOCKED)
			opti->tmp_p[j++] = ft_path_length(adj_mat, i);
		i += 1;
	}
	ft_bubble_sort(opti->tmp_p, j);
	ft_process_set(opti, j);
	if (opti->tmp >= opti->res && opti->res != 0)
		return (ft_recover_set(data, adj_mat, opti));
	else if (opti->tmp < opti->res || opti->res == 0)
		return (ft_save_new_set(data, adj_mat, opti));
}