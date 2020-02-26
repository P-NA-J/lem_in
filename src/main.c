/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pauljull <pauljull@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/18 14:35:19 by pauljull          #+#    #+#             */
/*   Updated: 2020/02/25 16:22:17 by aboitier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

/*
**	Fonction qui affiche ERROR et free ce qui doit l'être.
*/

int	ft_error(t_map *data)
{
	ft_putstr_fd("ERROR\n", 1);
	ft_free_all(data);
	return (FALSE);
}

/*
**	Fonction qui affiche l'usage lors d'une utilisation hors des cas d'usage.
*/

int	ft_usage(t_map *data)
{
	ft_free_all(data);
	ft_putstr_fd("USAGE\n", 2);
	return (FALSE);
}

/*
**	On parse le fichier.
**	On parcourt une première fois afin de supprimer les culs de sac.
**	On parcourt plusieurs fois afin de remodeler le graphe pour faire
**	apparaitre le plus de chemin sans collision de start à end.
**	On distribue les fourmis de manière équitable entre les différents
**	chemins qu'on a trouvé.
**	Finalement, on affiche le parcours de chaque fourmi et on free
**	toutes nos structures.
*/

int	main(void)
{
	t_map	*data;

	if ((data = parser()) == NULL)
		return (FALSE);
	if (data->adj_mat[data->start->index][data->end->index] == UNCHANGED)
		return (ft_s_to_e(data));
	ft_clean(data, data->adj_mat);
	if (ft_bhandari(data, data->adj_mat) == FALSE)
		return (ft_usage(data));
	if (data->nb_path == 0)
		return (ft_error(data));
	if (!(ft_print(data, data->path_tab, data->nb_path)))
		return (ft_error(data));
	return (0);
}
