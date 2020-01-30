/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_distribution.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pauljull <pauljull@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/20 08:59:33 by pauljull          #+#    #+#             */
/*   Updated: 2020/01/30 13:10:26 by pauljull         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/lem_in.h"

/*
	Fonction qui va redistribuer les fourmis de maniere équitable.
	entre les différents chemin en prenant en compte la taille des chemin.
*/

void	ft_distribution(int **tab_path, int nb_path, int nb_ants)
{
	int t;
	int i;

	t = 0;
	while (nb_ants > 0)
	{
		i = 0;
		t += 1;
		while (nb_ants > 0 && i < nb_path)
		{
			if (t >= tab_path[i][0])
			{
				tab_path[i][1] += 1;
				nb_ants -= 1;
			}
			i += 1;
		}
	}
}
