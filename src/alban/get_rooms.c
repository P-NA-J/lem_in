/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_rooms.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pauljull <pauljull@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/05 18:40:24 by aboitier          #+#    #+#             */
/*   Updated: 2020/02/25 15:19:18 by aboitier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/lem_in.h"
#include <stdlib.h>

int				get_nb_rooms(char *buffer)
{
	int		nb_rooms;
	char	*tmp;

	tmp = buffer;
	nb_rooms = 0;
	while (*tmp && (count_char_until(tmp, '-', '\n') == 0))
	{
		if (*tmp == '#')
		{
			tmp += ft_strclen(tmp, '\n') + 1;
			continue ;
		}
		if (count_char_until(tmp, ' ', '\n') == 2)
			nb_rooms++;
		tmp = tmp + ft_strclen(tmp, '\n') + 1;
	}
	return (nb_rooms);
}

int				check_room_line(t_preparse *prep, t_map *data)
{
	if (prep->buffer[0] == '\n' || prep->buffer[0] == 'L'
				|| prep->buffer[0] == ' ')
		return (FALSE);
	else if (prep->buffer[0] == '#')
		return (parse_comment(prep, data));
	return (TRUE);
}

int				get_next_room(t_preparse *prep, t_map *data)
{
	while (*(prep->buffer) && count_char_until(prep->buffer, '-', '\n') != 1)
	{
		if (check_room_line(prep, data) == FALSE)
			return (FALSE);
		if (count_char_until(prep->buffer, ' ', '\n') == 2)
		{
			if (valid_coords(prep->buffer) == FALSE)
				return (FALSE);
			if (create_room(data, prep) == FALSE)
				return (FALSE);
		}
		else if (count_char_until(prep->buffer, ' ', '\n') != 2
						&& count_char_until(prep->buffer, '-', '\n') != 1
						&& prep->buffer[0] != '\n')
			return (FALSE);
		if (count_char_until(prep->buffer, '-', '\n') != 1)
			prep->buffer += ft_strclen(prep->buffer, '\n') + 1;
	}
	return (TRUE);
}

int				parse_rooms(t_map **data, t_preparse *prep)
{
	while (*(prep->buffer) && prep->curr_room < (*data)->nb_rooms
				&& (count_char_until(prep->buffer, ' ', '\n') == 2
				|| *(prep->buffer) == '#')
				&& count_char_until(prep->buffer, '-', '\n') != 1)
	{
		if (get_next_room(prep, *data) == FALSE)
			return (FALSE);
		if (count_char_until(prep->buffer, '-', '\n') != 1)
			prep->buffer += ft_strclen(prep->buffer, '\n') + 1;
	}
	return (TRUE);
}

/*
**	Count number of rooms
** 	Alloc memory for rooms tab
*/

t_room			**get_rooms(t_map *data, t_preparse *prep)
{
	t_room	**rooms;

	rooms = NULL;
	if ((data->nb_rooms = get_nb_rooms(prep->buffer)) == 0)
		return (NULL);
	if (!(rooms = (t_room **)malloc(sizeof(t_room *) * data->nb_rooms)))
		return (NULL);
	return (rooms);
}
