/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pauljull <pauljull@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/18 14:35:19 by pauljull          #+#    #+#             */
/*   Updated: 2020/02/11 15:10:24 by pauljull         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

/*
	On parse le fichier.
	On parcourt une première fois afin de supprimer les culs de sac.
	On parcourt plusieurs fois afin de remodeler le graphe pour faire apparaitre le plus de chemin sans collision de start à end.
	On distribue les fourmis de manière équitable entre les différents chemins qu'on a trouvé.
	Finalement, on affiche le parcours de chaque fourmi et on free toutes nos structures.
*/

int	main(void)
{
	t_map	*data;
	t_path	*path;

	if ((data = parser()) == NULL)
		return (FALSE);
	ft_clean(data, data->adj_mat);
	if (ft_bhandari(data, data->adj_mat) == NULL)
	{
		write(1, "ERROR\n", 6);
		return ((int)which_error(data, 2));
	}
	path = ft_path(data, data->adj_mat);
//	ft_distribution(path, data);
//	ft_debug_collission(data);
	return (0);
}
