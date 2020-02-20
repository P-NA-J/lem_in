/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_matrix_modif.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pauljull <pauljull@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/20 15:15:19 by pauljull          #+#    #+#             */
/*   Updated: 2020/02/20 19:35:29 by pauljull         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/lem_in.h"

/*
**	Fonction qui inscrit une valeur pour un lien dans les deux sens.
*/

int			**ft_mat_mirror_change(int **adj_mat, int value, int i_1, int i_2)
{
	adj_mat[i_1][i_2] = value;
	adj_mat[i_2][i_1] = value;
	return (adj_mat);
}

/*
**	Fonction qui supprime les liens inutiles et
**	set a UNCHANGED le bon lien sur une ligne
*/

static void	ft_clean_line(int *line, int nb_rooms)
{
	int	i;

	i = 0;
	while (i < nb_rooms)
	{
		if (line[i] == BLOCKED)
			line[i] = UNCHANGED;
		else
			line[i] = NO_LINK;
		i++;
	}
}

/*
**	Fonction qui supprime les liens inutile afin de
**	simplifier au maximum la matrice et faire apparaitre
**	les chemins empruntable.
*/

void		ft_clean_matrix(t_map *data, int **adj_mat)
{
	int	i;
	int	nb_rooms;

	nb_rooms = data->nb_rooms;
	i = 0;
	while (i < nb_rooms)
	{
		ft_clean_line(adj_mat[i], nb_rooms);
		i++;
	}
}

static void	ft_matrix_set_link(int **adj_mat, t_room *current,
								int state_1, int state_2)
{
	adj_mat[current->index][current->prev->index] = state_1;
	adj_mat[current->prev->index][current->index] = state_2;
}

/*
**	Fonction qui coupe les liens qui ont été remontés
**	et actualise l'état des autre liens du chemin trouvé.
*/

void		ft_reset_matrix(t_map *data, int **adj_mat)
{
	t_room	*current;
	t_room	*start;
	int		i_tmp;

	start = data->start;
	current = data->end;
	while (current != start)
	{
		i_tmp = current->index;
		if (adj_mat[current->index][current->prev->index] == UNCHANGED)
		{
			if (current->prev == start)
				ft_matrix_set_link(adj_mat, current, INFINY, BLOCKED);
			else
				ft_matrix_set_link(adj_mat, current, AUGMENTED, BLOCKED);
		}
		else if (adj_mat[current->index][current->prev->index] == BLOCKED)
			ft_mat_mirror_change(adj_mat, TO_CUT,
								current->index, current->prev->index);
		current = current->prev;
		data->opti.index = i_tmp;
	}
}
