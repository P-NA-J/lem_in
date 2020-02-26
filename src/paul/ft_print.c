/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pauljull <pauljull@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/12 16:41:48 by pauljull          #+#    #+#             */
/*   Updated: 2020/02/25 16:23:34 by aboitier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/lem_in.h"

/*
**	Fonction qui inscrit dans le buffer le déplacement d'une fourmi et
**	décrémente le nombre de fourmis restantes lorsqu'une fourmis atteint end.
*/

int		ft_print_move(t_map *data, int no_ants, int no_room)
{
	char	*tmp;

	if (no_room == data->end->index)
	{
		data->nb_ants -= 1;
	}
	ft_putstr_buffer(&(data->buff), "L", 1);
	if (!(tmp = ft_itoa(no_ants)))
		return (FALSE);
	ft_putstr_buffer(&(data->buff), tmp,
					ft_strlen(tmp));
	free(tmp);
	ft_putstr_buffer(&(data->buff), "-", 1);
	ft_putstr_buffer(&(data->buff), data->rooms[no_room]->name,
					ft_strlen(data->rooms[no_room]->name));
	ft_putstr_buffer(&(data->buff), " ", 1);
	return (TRUE);
}

/*
**	Fonction qui gere l'avancement des fourmis sur un chemin et qui
**	appelle la fonction de print dans le buffer
**	pour un déplacement de fourmis.
*/

int		ft_edit_path(t_map *data, int path[2][PRIME])
{
	int	i;

	i = path[0][0] - 1;
	while (i > 1)
	{
		if (path[1][i] != 0)
		{
			path[1][i + 1] = path[1][i];
			path[1][i] = 0;
			if (!(ft_print_move(data, path[1][i + 1], path[0][i + 1])))
				return (FALSE);
		}
		if (i == 2 && path[1][1] != 0)
		{
			path[1][2] = path[1][0];
			path[1][0] += 1;
			path[1][1] -= 1;
			if (!(ft_print_move(data, path[1][i], path[0][i])))
				return (FALSE);
		}
		i -= 1;
	}
	return (TRUE);
}

void	ft_print_file(t_map *data)
{
	int	len;

	len = ft_strlen(data->preparse->tmp_buff);
	write(1, data->preparse->tmp_buff, len);
	write(1, "\n", 1);
	if (data->preparse->tmp_buff[len - 1] != '\n')
		write(1, "\n", 1);
}

/*
**	Fonction qui va appeler la fonction d'avancement sur un chemin
**	tant qu'il y a des fourmis qui ne sont pas sur end.
*/

int		ft_print(t_map *data, int path_tab[MAX_PATH][2][PRIME], int nb_path)
{
	int	i;

	ft_print_file(data);
	while (data->nb_ants != 0)
	{
		i = 0;
		while (i < nb_path && data->nb_ants != 0)
		{
			if (!(ft_edit_path(data, path_tab[i])))
				return (FALSE);
			i += 1;
		}
		ft_putstr_buffer(&(data->buff), "\n", 1);
	}
	ft_flush_buffer(&(data->buff));
	return (TRUE);
}
