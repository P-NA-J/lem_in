/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_rooms.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboitier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/05 18:40:24 by aboitier          #+#    #+#             */
/*   Updated: 2019/12/05 18:44:16 by aboitier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"
#include <stdlib.h>


int				get_nb_rooms(char *buffer)
{
	int		nb_rooms;
	int		i;
	
	nb_rooms = 0;
	i = 0;
	while (buffer[i] && buffer[i] != '-')
	{
		if (buffer[i] == '\n')
			nb_rooms++;
		else if (buffer[i] == '#')
			while (buffer[i] && buffer[i] != '\n' && buffer[i + 1] != '\0')
				i++;
		i++;
	}	
	return (nb_rooms);
}

t_room			*get_next_room(t_preparse *prep, t_map *data, int opt)
{
	t_room 	*new;

	new = NULL;
	while (*(prep->buffer) && *(prep->buffer) != '\n')
	{
		if (prep->buffer[0] == '\n' || prep->buffer[0] == 'L' || prep->buffer[0] == ' ')
			return (NULL);
		else if (prep->buffer[0] == '#')
			return (parse_comment(prep, data));
		else if (count_char_until(prep->buffer, ' ', '\n') == 2)
		{
			if (!(new = (t_room *)malloc(sizeof(t_room))))
				return (NULL);
			if (!(new->name = ft_strcsub(prep->buffer, ' ')))
				return (NULL);
			if (opt == 1)
				data->start = new;
			else if (opt == 2)
				data->end = new;
		}
		prep->buffer += ft_strclen(prep->buffer, '\n');
	}
	return (new);
}

int			parse_rooms(t_map **data, t_preparse *prep, t_room **rooms)
{
	int 		curr_room;
	uint32_t	hashed_name;

	curr_room = 0;
	hashed_name = 0;
	while (*(prep->buffer) && curr_room < (*data)->nb_rooms)
	{
		if (!(rooms[curr_room] = get_next_room(prep, *data, 0)))
			return (FALSE);
		hashed_name = jenkins_hash(rooms[curr_room]->name);	
		while (prep->hashed_rooms[hashed_name].name)
			hashed_name = (hashed_name < PRIME) ? hashed_name += 1 : 0;
		(*data)->preparse->hashed_rooms[hashed_name] = *rooms[curr_room];
		rooms[curr_room]->hash = hashed_name;
		curr_room++;
		prep->buffer += ft_strclen(prep->buffer, '\n') + 1;
	}
	return (TRUE);
}

t_room			**get_rooms(t_map *data, t_preparse *prep)
{
	t_room	**rooms;
	char	**tmp;

	tmp = &prep->buffer;
	rooms = NULL;
	if ((data->nb_rooms = get_nb_rooms(prep->buffer)) == 0)
		return (NULL);
	if (!(rooms = (t_room **)malloc(sizeof(t_room *) * data->nb_rooms)))
		return (NULL);
	if ((parse_rooms(&data, prep, rooms)) == FALSE)
		return (NULL);

	free(tmp);
	return (rooms);
}

