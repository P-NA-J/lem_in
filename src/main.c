/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pauljull <pauljull@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/18 14:35:19 by pauljull          #+#    #+#             */
/*   Updated: 2020/01/30 17:10:16 by pauljull         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

/*
	On parse le fichier.
	On parcours une première fois afin de supprimer les culs de sac.
	On parcours plusieurs fois afin de remodeler le graphe pour faire apparaitre le plus de chemin sans collision de start à end.
	On distribue les fourmis de manière équitable entre les différents chemins qu'on a trouvé.
	Finalement, on affiche le parcours de chaque fourmi et on free toutes nos structures.
*/

int	main(void)
{
	t_map	*data;

	if ((data = parser()) == NULL)
		return (FALSE);
	ft_clean(data, data->adj_mat);
	if (ft_bhandari(data, data->adj_mat) == NULL)
	{
		data = which_error(data, 2);
		return (0);
	}
	print_info(data);
//	ft_debug_path(data, data->end, adj_mat);
//	PROCEDURE DE DISTRIBUTION ET DE PRINT
//	PROCEDURE DE FREE
	return (0);
}
