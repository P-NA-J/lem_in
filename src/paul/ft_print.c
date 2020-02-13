/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pauljull <pauljull@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/12 16:41:48 by pauljull          #+#    #+#             */
/*   Updated: 2020/02/12 17:10:55 by pauljull         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/lem_in.h"

/*
	Fonction qui inscrit dans le buffer le déplacement d'une fourmi et décrémente le nombre de fourmis restantes lorsqu'une fourmis atteint end.
*/

void	ft_print_move(t_map *data, int no_ants, int no_room)
{
	if (no_room == data->end->index)
		data->nb_ants -= 1;
	ft_putstr_buffer(&(data->buff), "L", 1);
	ft_putstr_buffer(&(data->buff), ft_itoa(no_ants), ft_nb_digit(10, "u", no_ants));
	ft_putstr_buffer(&(data->buff), "-", 1);
	ft_putstr_buffer(&(data->buff), data->rooms[no_room]->name, ft_strlen(data->rooms[no_room]->name));
	ft_putstr_buffer(&(data->buff), " ", 1);
}

/*
	Fonction qui gere l'avancement des fourmis sur un chemin et qui appelle la fonction de print dans le buffer pour un déplacement de fourmis.
*/

void	ft_edit_line(t_map *data, int **path)
{
	int	i;

	i = path[0][0] - 1;
	while (i > 0)
	{
		if (path[1][i] != 0)
		{
			path[1][i + 1] = path[i];
			ft_print_move(data, path[1][i + 1], path[0][i + 1]);
		}
		i -= 1;
	}
}

/*
	Fonction qui va appeler la fonction d'avancement sur un chemin tant qu'il y a des formis qui ne sont pas sur end.
*/

void	ft_print(t_map *data, int ***path_tab, int nb_path)
{
	int	i;

	while (data->nb_ants != 0)
	{
		i = 0;
		while (i < nb_path && data->nb_ants != 0)
		{
			ft_edit_line(data, path_tab[i]);
			i += 1;
		}
		ft_putstr_buffer(&(data->buff), "\n", 1);
	}
}