/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_rooms.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pauljull <pauljull@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/05 18:40:24 by aboitier          #+#    #+#             */
/*   Updated: 2019/12/21 09:00:13 by pauljull         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/lem_in.h"
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

int			end_or_start(t_preparse *prep, t_room *stend, t_map *data)
{
	if (prep->s_or_e == 1)
		data->start = stend;
	else if (prep->s_or_e == 2)
		data->end = stend;
	prep->s_or_e = 0;
	return (TRUE);	
}

// add checks if start|end is already filled
t_room			*get_next_room(t_preparse *prep, t_map *data)
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
			ft_bzero(new, sizeof(t_room));
			if (!(new->name = ft_strcsub(prep->buffer, ' ')))
				return (NULL);
			if (prep->s_or_e)
				end_or_start(prep, new, data);
		}
		prep->buffer += ft_strclen(prep->buffer, '\n');
	}
	return (new);
}

uint32_t	get_hashed_name(t_preparse *prep, char *name)
{
	int			max_rooms;
	uint32_t	hashed_name;

	max_rooms = 0;
	hashed_name = jenkins_hash(name);	
	while (prep->hashed_rooms[hashed_name].name && ++max_rooms)
	{
		hashed_name = (hashed_name < PRIME - 1) ? hashed_name += 1 : 0;
		if (max_rooms > PRIME)
			return (FALSE);
	}
	return (hashed_name);
}

// add check for similar names
int			parse_rooms(t_map **data, t_preparse *prep, t_room **rooms)
{
	int 		curr_room;
	uint32_t	hashed_name;

	curr_room = 0;
	hashed_name = 0;
	while (*(prep->buffer) && curr_room < (*data)->nb_rooms)
	{
		if (!(rooms[curr_room] = get_next_room(prep, *data)))
			return (FALSE);
		hashed_name = get_hashed_name(prep, rooms[curr_room]->name);
		rooms[curr_room]->hash = hashed_name;
		rooms[curr_room]->index = curr_room;
		rooms[curr_room]->features = UNQUEUE;
		rooms[curr_room]->path_occurence = 0;
		prep->hashed_rooms[hashed_name] = *rooms[curr_room];
		curr_room++;
		prep->buffer += ft_strclen(prep->buffer, '\n') + 1;
	}
	return (TRUE);
}

t_room			**get_rooms(t_map *data, t_preparse *prep)
{
	t_room	**rooms;

	rooms = NULL;
	if ((data->nb_rooms = get_nb_rooms(prep->buffer)) == 0)
		return (NULL);
	if (!(rooms = (t_room **)malloc(sizeof(t_room *) * data->nb_rooms)))
		return (NULL);
	if ((parse_rooms(&data, prep, rooms)) == FALSE)
		return (NULL);
	return (rooms);
}

