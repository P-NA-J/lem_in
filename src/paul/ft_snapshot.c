/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_snapshot.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pauljull <pauljull@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/13 18:05:51 by pauljull          #+#    #+#             */
/*   Updated: 2020/02/20 21:29:02 by pauljull         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/lem_in.h"

/*
**	Fonction qui répartir équitablement un certain nombre de fourmis
**	entre un certain nombre de chemins.
*/

void	ft_dispatch_ants(t_opti *opti, int to_add, int nb_path, int *nb_ants)
{
	int	i;
	int	ants_remaining;

	ants_remaining = *nb_ants;
	i = 0;
	while (i < nb_path && ants_remaining > 0)
	{
		opti->distrib_p[0][i] += to_add;
		ants_remaining -= to_add;
		i += 1;
	}
	*nb_ants = ants_remaining;
}

/*
**	Fonction qui va répartir les fourmis entre les différents
**	chemins du set que évalue.
*/

void	ft_distribution(t_opti *opti, int nb_ants, int nb_path)
{
	int	i;
	int	to_add;

	i = 0;
	while (i < nb_path - 1)
	{
		to_add = opti->len_p[0][i + 1] - opti->len_p[0][i];
		if (to_add * (i + 1) > nb_ants)
		{
			ft_dispatch_ants(opti, nb_ants / (i + 1), i + 1, &nb_ants);
			if (nb_ants != 0)
				ft_dispatch_ants(opti, 1, i + 1, &nb_ants);
			return ;
		}
		else
			ft_dispatch_ants(opti, to_add, i + 1, &nb_ants);
		i += 1;
	}
	to_add = nb_ants;
	ft_dispatch_ants(opti, to_add / nb_path, nb_path, &nb_ants);
	if (nb_ants != 0)
		ft_dispatch_ants(opti, 1, nb_path, &nb_ants);
}

/*
**	Fonction qui va calculer la longueur d'un chemin
**	et inscrire cette longueur dans opti->len_p
*/

int		ft_calcul_length(t_map *data, int **adj_mat, int index)
{
	int	len;
	int	end_i;

	len = 1;
	end_i = data->end->index;
	while (index != end_i)
	{
		len += 1;
		index = ft_go_to_next(adj_mat, data->rooms[index], BLOCKED, BLOCKED);
	}
	return (len + 1);
}

/*
**	Fonction qui calcule le nombre de path.
*/

int		ft_calcul_nb_path(int **adj_mat, t_room *start)
{
	int	nb_link;
	int	i;
	int	count;

	count = 0;
	nb_link = start->nb_link;
	i = 0;
	while (i < nb_link)
	{
		if (adj_mat[START][start->link[i]] == BLOCKED)
			count += 1;
		i += 1;
	}
	return (count);
}

/*
**	Fonction qui va générer un snapshot et comparer par rapport
**	au meilleur snapshot.
*/

void	ft_snapshot(t_map *data, t_opti *opti, t_room *start)
{
	int	i;
	int	j;
	int	nb_link;

	nb_link = start->nb_link;
	data->nb_path = ft_calcul_nb_path(data->adj_mat, start);
	i = 0;
	j = 0;
	while (i < nb_link)
	{
		if (data->adj_mat[START][start->link[i]] == BLOCKED)
		{
			opti->index_p[0][j] = start->link[i];
			opti->len_p[0][j] = ft_calcul_length(data, data->adj_mat,
												start->link[i]);
			j += 1;
		}
		i += 1;
	}
	ft_bubble_sort(opti, data->nb_path);
	ft_distribution(opti, data->nb_ants, data->nb_path);
}
