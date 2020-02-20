/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_evaluate_snapshot.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pauljull <pauljull@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/18 15:49:24 by pauljull          #+#    #+#             */
/*   Updated: 2020/02/20 19:27:22 by pauljull         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/lem_in.h"

/*
**	Remet a zero path_tab.
*/

void		ft_clean_path_tab(t_map *data)
{
	int	i;

	i = 0;
	while (i < data->nb_path)
	{
		ft_clean_tab(data->path_tab[i][0], MAX_LEN_PATH);
		ft_clean_tab(data->path_tab[i][1], MAX_LEN_PATH);
		i += 1;
	}
}

/*
**	Fonction qui va confirmer la modification de la matrice
**	et couper les liens qui doivent être coupés.
*/

int			ft_confirm_matrix(t_map *data, int **adj_mat, int index)
{
	int	prev;

	prev = data->rooms[index]->prev->index;
	while (prev != data->start->index)
	{
		if (adj_mat[index][prev] == TO_CUT)
			ft_mat_mirror_change(adj_mat, NO_LINK, prev, index);
		prev = ft_go_to_next(adj_mat, data->rooms[prev],
							AUGMENTED, INFINY);
		index = prev;
	}
	ft_clean_path_tab(data);
	ft_path(data);
	return (TRUE);
}

/*
**	Fonction qui va restaurer l'ancien état de la matrice.
*/

int			ft_unset_matrix(t_map *data, int **adj_mat, int index)
{
	int	prev;
	int	tmp_prev;

	prev = index;
	index = data->end->index;
	while (index != data->start->index)
	{
		if (adj_mat[index][prev] == TO_CUT)
		{
			adj_mat[index][prev] = BLOCKED;
			adj_mat[prev][index] = AUGMENTED;
		}
		else
			ft_mat_mirror_change(adj_mat, UNCHANGED, prev, index);
		tmp_prev = prev;
		prev = ft_go_to_next(adj_mat, data->rooms[prev],
							AUGMENTED, INFINY);
		index = tmp_prev;
	}
	return (FALSE);
}

static void	ft_save_snapshot(t_opti *opti, int i)
{
	ft_cpy_tab(opti->distrib_p[1], opti->distrib_p[0], i);
	ft_clean_tab(opti->distrib_p[0], i);
	ft_cpy_tab(opti->len_p[1], opti->len_p[0], i);
	ft_clean_tab(opti->len_p[0], i);
	ft_cpy_tab(opti->index_p[1], opti->index_p[0], i);
	ft_clean_tab(opti->index_p[0], i);
}

/*
**	Fonction qui va évaluer si le snapshot en cours
**	est plus performant que le meilleur déjà enregistrer.
*/

int			ft_evaluate_snapshot(t_map *data, int **adj_mat,
						t_opti *opti, int nb_path)
{
	int	complexity_p;
	int	tmp;
	int	i;

	i = 0;
	complexity_p = INT_MAX;
	while (i < nb_path && opti->distrib_p[0][i] > 0)
	{
		tmp = opti->len_p[0][i] + opti->distrib_p[0][i] - 1;
		if (tmp < complexity_p)
			complexity_p = tmp;
		i += 1;
	}
	if (complexity_p >= opti->res)
	{
		data->nb_path -= 1;
		return (ft_unset_matrix(data, adj_mat, opti->index));
	}
	else
	{
		data->nb_path = i;
		opti->res = complexity_p;
		ft_save_snapshot(opti, i);
		return (ft_confirm_matrix(data, adj_mat, opti->index));
	}
}
