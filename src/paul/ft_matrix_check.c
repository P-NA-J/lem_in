/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_matrix_check.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pauljull <pauljull@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/18 15:57:44 by pauljull          #+#    #+#             */
/*   Updated: 2020/02/18 15:59:25 by pauljull         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/lem_in.h"

/*
	Fonction qui renvoie l'adresse du premier lien d'une salle qui match avec un état passé en paramètre.
*/

int		ft_go_to_next(int **adj_mat, t_room *current, int state, int ntm)
{
	int	i;
	int	nb_link;
	int	index;
	int	*link;

	index = current->index;
	link = current->link;
	nb_link = current->nb_link;
	i = 0;
	while (i < nb_link)
	{
		if (adj_mat[index][link[i]] == state || adj_mat[index][link[i]] == ntm)
			return (link[i]);
		i += 1;
	}
	return (IGNORE);
}

/*
	Fonction qui renvoie l'index de la salle qui est relié a une salle donnée
	avec un lien dans un certain état.
*/

int		ft_check_line(t_room *to_add, int *line, int state)
{
	int	i;
	int	len;
	int index;

	len = to_add->nb_link;
	i = 0;
	while (i < len)
	{
		index = to_add->link[i];
		if (line[index] == state)
		{
			return (index);
		}
		i++;
	}
	return (IGNORE);
}

/*
	Fonction qui s'assure qu'il n'y a pas de lien augmenté sur une salle donnée.
*/

int		ft_line_check(t_room *to_add, int *line)
{
	int	i;
	int	len;
	int	index;

	len = to_add->nb_link;
	i = 0;
	while (i < len)
	{
		index = to_add->link[i];
		if (line[index] == AUGMENTED || line[index] == INFINY)
			return (index);
		i += 1;
	}
	return (IGNORE);
}
