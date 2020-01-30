/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_matrix.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pauljull <pauljull@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/20 15:15:19 by pauljull          #+#    #+#             */
/*   Updated: 2020/01/30 18:54:30 by pauljull         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/lem_in.h"

/*
	Fonction qui renvoie l'index de la salle suivante.
*/

int	ft_go_to_next(int *line, int nb_rooms)
{
	int	i;

	i = -1;
	while (++i < nb_rooms)
	{
		if (line[i] == UNCHANGED)
			return (i);
	}
	return (IGNORE);
}

/*
	Fonction qui calcule la longueur d'un chemin.
*/

int	ft_path_length(int **adj_mat, int index, int end_index, int nb_rooms)
{
	int nb;

	nb = 1;
	while (index != end_index)
	{
		nb += 1;
		index = ft_go_to_next(adj_mat[index], nb_rooms);
	}
	return (nb);
}

/*
	Fonction qui inscrit une valeur pour un lien dans les deux sens.
*/

int		**ft_mat_mirror_change(int **adj_mat, int value, int i_1, int i_2)
{
	adj_mat[i_1][i_2] = value;
	adj_mat[i_2][i_1] = value;
	return (adj_mat);
}

/*
	Fonction qui renvoie l'index de la salle qui est relié a une salle donnée
	avec un lien dans un certain état.
*/

int		ft_check_line(int *line, int len, int nb)
{
	int	i;

	i = 0;
	while (i < len)
	{
		if (line[i] == nb)
			return (i);
		i += 1;
	}
	return (-1);
}

/*
	Fonction qui s'assure qu'il n'y a pas de lien augmenté sur une salle donnée.
*/

int		ft_line_check(int *line, int len)
{
	int	i;

	i = 0;
	while (i < len)
	{
		if (line[i] == AUGMENTED || line[i] == INFINY)
			return (i);
		i += 1;
	}
	return (-1);
}

/*
	Fonction qui indique la longueur de chaque chemin
*/

void	ft_path_set(int **adj_mat, t_map *data)
{
	int	i;
	int	nb_rooms;

	nb_rooms = data->nb_rooms;
	i = -1;
	while (++i < nb_rooms)
	{
		if (adj_mat[data->start->index][i] == UNCHANGED)
			adj_mat[data->start->index][i] = ft_path_length(adj_mat, i, data->end->index, nb_rooms);
	}
}

/*
	Fonction qui supprime les liens inutiles et set a UNCHANGED le bon lien sur une ligne
*/

static void	ft_clean_line(int *line, int nb_rooms)
{
	int	i;

	i = -1;
	while (++i < nb_rooms)
	{
		if (line[i] == BLOCKED)
			line[i] = UNCHANGED;
		else
			line[i] = NO_LINK;
	}
}

/*
	Fonction qui supprime les liens inutile afin de simplifier au maximum la matrice
	et faire apparaitre les chemins empruntable.
*/

void	ft_clean_matrix(t_map *data, int **adj_mat)
{
	int	i;
	int	nb_rooms;

	nb_rooms = data->nb_rooms;
	i = -1;
	while (++i < nb_rooms)
		ft_clean_line(adj_mat[i], nb_rooms);
	ft_path_set(adj_mat, data);
}

/*
	Fonction qui coupe les liens qui ont été remontés et actualise l'état des autre liens du chemin trouvé.
*/

void	ft_reset_matrix(t_map *data, int **adj_mat)
{
	t_room *current;
	t_room	*start;

	start = data->start;
	current = data->end;
	while (current != start)
	{
		if (adj_mat[current->index][current->prev->index] == UNCHANGED)
		{
			if (current->prev == start)
			{
				adj_mat[current->index][current->prev->index] = INFINY;
				adj_mat[current->prev->index][current->index] = BLOCKED;
			}
			else
			{
				adj_mat[current->index][current->prev->index] = AUGMENTED;
				adj_mat[current->prev->index][current->index] = BLOCKED;
			}
		}
		else if (adj_mat[current->index][current->prev->index] == BLOCKED)
			ft_mat_mirror_change(adj_mat, NO_LINK, current->index, current->prev->index);
		current = current->prev;
	}
}
