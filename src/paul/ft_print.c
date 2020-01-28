/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pauljull <pauljull@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/08 12:58:56 by pauljull          #+#    #+#             */
/*   Updated: 2020/01/28 16:33:02 by pauljull         ###   ########.fr       */
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

int		*ft_ants_cell_init(t_map *data, int *tab, int i)
{
	int	j;
	int	*ants;

	j = 0;
	if (!(ants = (int *)malloc(sizeof(int) * 3)))
		return (NULL);
	ants[0] = i + 1;
	ants[2] = data->start->index;
	while (j < data->nb_path)
	{
		if (tab[j] > 0)
		{
			ants[1] = j;
			tab[j] -= 1;
			break ;
		}
		else
			j += 1;
	}
	return (ants);
}

int		**ft_ants_tab_init(int *tab, t_map *data)
{
	int	**ants;
	int	i;

	i = 0;
	if (!(ants = (int **)malloc(sizeof(int *) * data->nb_ants)))
		return (NULL);
	while (i < data->nb_ants)
	{
		ants[i] = ft_ants_cell_init(data, tab, i);
		i += 1;
	}
	return (ants);
}

void	ft_print_move(t_buff *buff, t_map *data, int *ants)
{
	ft_write_in_buffer(buff, 'L', 1);
	ft_putstr_buffer(buff, ft_itoa(ants[0]), ft_nb_digit(10, "u", ants[0]));
	ft_write_in_buffer(buff, '-', 1);
	ft_putstr_buffer(buff, data->rooms[ants[2]]->name,
	ft_strlen(data->rooms[ants[2]]->name));
	ft_write_in_buffer(buff, ' ', 1);
}

void	ft_move_on(int *ants, int *tab, t_map *data, t_buff *buff)
{
	int	tmp;
	int	i;

	tmp = ants[2];
	i = 2;
	data->rooms[ants[2]]->features = EMPTY;
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
		data->rooms[ants[2]]->features = OCCUPIED;
	ft_print_move(buff, data, ants);
}

t_bool	ft_next_room(t_map *data, int curr_room, int *path)
{
	int		tmp_room;
	int		i;

	i = 2;
	tmp_room = path[2];
	while (tmp_room != curr_room)
		tmp_room = path[++i];
	if (data->rooms[path[i + 1]]->features == OCCUPIED)
		return (FALSE);
	return (TRUE);
}

void	ft_line_edit(int **ants, t_map *data, int **tab, int *ants_count)
{
	int	i;

	i = 0;
	while (i < data->nb_ants)
	{
		if (ants[i][2] == data->start->index && tab[ants[i][1]][1] != 0
		&& ft_next_room(data, ants[i][2], tab[ants[i][1]]) == TRUE)
		{
			tab[ants[i][1]][1] -= 1;
			ft_move_on(ants[i], tab[ants[i][1]], data, &(data->buff));
		}
		else if (ants[i][2] != data->start->index
		&& ants[i][2] != data->end->index && ants[i][2] != -1
		&& ft_next_room(data, ants[i][2], tab[ants[i][1]]) == TRUE)
			ft_move_on(ants[i], tab[ants[i][1]], data, &(data->buff));
		if (ants[i][2] == data->end->index)
		{
			*ants_count += 1;
			ants[i][2] = -1;
		}
		i += 1;
	}
	ft_write_in_buffer(&(data->buff), '\n', 1);
}

void	ft_print_file(t_map *data)
{
	ft_bzero(&(data->buff), sizeof(data->buff));
	ft_putstr_buffer(&(data->buff), data->preparse->tmp_buff,
	ft_strlen(data->preparse->tmp_buff));
	if (data->preparse->tmp_buff[ft_strlen(data->preparse->tmp_buff) - 1] != '\n')
		ft_write_in_buffer(&(data->buff), '\n', 2);
	else
		ft_write_in_buffer(&(data->buff), '\n', 1);
}

int		**ft_print(int **tab, t_map *data)
{
	int		**ants;
	int		ants_count;

	if (!(ants = ft_ants_tab_init(ft_tmp_tab(tab, data->nb_path), data)))
		return (NULL);
//	ft_print_file(data);
	ants_count = 0;
	while (ants_count != data->nb_ants)
		ft_line_edit(ants, data, tab, &ants_count);
	ft_flush_buffer(&(data->buff));
	return (ants);
}
