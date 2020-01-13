/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pauljull <pauljull@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/08 12:58:56 by pauljull          #+#    #+#             */
/*   Updated: 2020/01/13 17:38:01 by pauljull         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/lem_in.h"

void	ft_set_correct_path(int *ants, t_map *data, int *tab, int *j)
{
	ants[1] = *j;
	tab[*j] -= 1;
	*j += 1;
	if (*j >= data->nb_path)
		*j = 0;
	ants[2] = data->start->index;
}

int		**ft_ants_tab_init(int *tab, t_map *data)
{
	int	**ants;
	int	i;
	int	j;

	if (!(ants = (int **)malloc(sizeof(int *) * data->nb_ants)))
		return (NULL);
	i = 0;
	j = 0;
	while (i < data->nb_ants)
	{
		if (!(ants[i] = (int *)malloc(sizeof(int) * 3)))
			return (NULL);
		ants[i][0] = i + 1;
		ants[i][1] = j;
		if (tab[j] > 0)
		{
			ft_set_correct_path(ants[i], data, tab, &j);
			i += 1;
		}
		else
			j = 0;
	}
	return (ants);
}

void	ft_move_on(int *ants, int *tab, t_map *data, t_buff *buff)
{
	int	tmp;
	int	i;

	tmp = ants[2];
	i = 2;
	while (i <= tab[0] + 1)
	{
		if (tab[i] == tmp)
		{
			tmp = tab[i + 1];
			break ;
		}
		i += 1;
	}
	ants[2] = tmp;
	if (ants[2] != data->end->index)
	{
		ft_write_in_buffer(buff, 'L', 1);
		ft_putstr_buffer(buff, ft_itoa(ants[0]), ft_nb_digit(10, "u", ants[0]));
		ft_write_in_buffer(buff, '-', 1);
		ft_putstr_buffer(buff, data->rooms[ants[2]]->name,
		ft_strlen(data->rooms[ants[2]]->name));
		ft_write_in_buffer(buff, ' ', 1);
	}
}

int		*ft_tmp_tab(int **tab, int nb_line)
{
	int	*tmp_tab;
	int	i;

	if (!(tmp_tab = (int *)malloc(sizeof(int) * nb_line)))
		return (NULL);
	i = 0;
	while (i < nb_line)
	{
		tmp_tab[i] = tab[i][1];
		i += 1;
	}
	return (tmp_tab);
}

void	ft_line_edit(int **ants, t_map *data, int **tab, int *ants_count)
{
	int	i;

	i = 0;
	while (i < data->nb_path)
	{
		if (ants[i][2] == data->start->index && tab[ants[i][1]][1] != 0)
		{
			tab[ants[i][1]][1] -= 1;
			ft_move_on(ants[i], tab[ants[i][1]], data, &(data->buff));
		}
		else if (ants[i][2] != data->start->index
		&& ants[i][2] != data->end->index && ants[i][2] != -1)
			ft_move_on(ants[i], tab[ants[i][1]], data, &(data->buff));
		if (ants[i][2] == data->end->index)
		{
			*ants_count += 1;
			ants[i][2] = -1;
		}
		i += 1;
	}
}

int		**ft_print(int **tab, t_map *data)
{
	int		**ants;
	int		ants_count;
	int		i;

	if (!(ants = ft_ants_tab_init(ft_tmp_tab(tab, data->nb_path), data)))
		return (NULL);
	ants_count = 0;
	i = 0;
	ft_bzero(&(data->buff), sizeof(data->buff));
	while (ants_count != data->nb_ants)
	{
		ft_line_edit(ants, data, tab, &ants_count);
		if (ants_count != data->nb_ants)
			ft_write_in_buffer(&(data->buff), '\n', 1);
	}
	ft_flush_buffer(&(data->buff));
	return (ants);
}
