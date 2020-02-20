/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_static_tab_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pauljull <pauljull@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/18 15:50:47 by pauljull          #+#    #+#             */
/*   Updated: 2020/02/20 19:53:25 by pauljull         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/lem_in.h"

/*
**	Fonction qui efface le contenu d'un tableau int [MAX_LEN_PATH]
*/

void	ft_clean_tab(int tab[MAX_LEN_PATH], int n)
{
	int	i;

	i = 0;
	while (i < n)
		tab[i++] = 0;
}

/*
**	Fonction qui copie une tableau d'int dans un autre.
*/

void	ft_cpy_tab(int dest[MAX_LEN_PATH], int src[MAX_LEN_PATH], int len)
{
	int	i;

	i = 0;
	while (i < len)
	{
		dest[i] = src[i];
		i += 1;
	}
}

/*
**	Fonction qui renvoie TRUE si une valeur est presente
**	dans un tableau de valeur.
*/

int		ft_int_is_present(int *index_p, int value)
{
	int	i;

	i = 0;
	while (index_p[i] != 0)
	{
		if (index_p[i] == value)
			return (TRUE);
		i += 1;
	}
	return (FALSE);
}
