/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_distribution.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pauljull <pauljull@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/20 08:59:33 by pauljull          #+#    #+#             */
/*   Updated: 2020/02/11 14:39:33 by pauljull         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/lem_in.h"

/*
	Fonction qui calcule le nombre de fourmi à envoyer sur un chemin donné dans le cas général (sum % nb_path == 0)
*/

int		ft_process_distrib(t_path *path, t_map *data)
{
	return (((data->nb_ants + data->sum_len_path - data->nb_path) / data->nb_path) + 1 - path->len);
}

/*
	Fonction qui va redistribuer les fourmis de maniere équitable.
	entre les différents chemin en prenant en compte la taille des chemin.
*/

void	ft_distribution(t_path *path, t_map *data)
{
	t_path	*head;
	int		verif_sum;

	head = path;
	verif_sum = 0;
	while (path != NULL)
	{
		printf("len = %d -----------\n", path->len);
		path = path->next;
	}
	printf("nb_ants = %d\nverif_sum = %d\nComplexite totale = %d\n", data->nb_ants, data->sum_len_path, (data->nb_ants + data->sum_len_path - data->nb_path) / data->nb_path);
}