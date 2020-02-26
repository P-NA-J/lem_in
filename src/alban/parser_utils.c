/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboitier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/30 17:19:11 by aboitier          #+#    #+#             */
/*   Updated: 2020/02/25 15:19:48 by aboitier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/lem_in.h"

int			set_room(t_room *new, int index, uint32_t hash)
{
	new->hash = hash;
	new->features = UNQUEUE;
	new->index = index;
	return (TRUE);
}

int			get_start_or_end(t_preparse *prep, t_room *new, t_map *data)
{
	if (prep->s_or_e == 1)
	{
		if (data->start)
			return (FALSE);
		data->start = new;
	}
	else if (prep->s_or_e == 2)
	{
		if (data->end)
			return (FALSE);
		data->end = new;
	}
	prep->s_or_e = 0;
	return (TRUE);
}

int			fix_room(t_preparse *prep, t_room *new, t_map *data)
{
	uint32_t	hash;
	int			index;

	if (!(hash = get_hashed_name(prep, new->name)))
		return (FALSE);
	if (prep->s_or_e)
		index = (prep->s_or_e == 1) ? 0 : data->nb_rooms - 1;
	else
		index = prep->curr_room++ + 1;
	set_room(new, index, hash);
	if (!(get_start_or_end(prep, new, data)))
		return (FALSE);
	if (index == data->nb_rooms)
		return (FALSE);
	data->rooms[index] = new;
	prep->hashed_rooms[hash] = *new;
	return (TRUE);
}

int			create_room(t_map *data, t_preparse *prep)
{
	t_room *new;

	new = NULL;
	if (!(new = (t_room *)ft_memalloc(sizeof(t_room))) \
			|| !(new->name = ft_strcsub(prep->buffer, ' ')))
		return (FALSE);
	if ((fix_room(prep, new, data) == FALSE))
	{
		free(new->name);
		free(new);
		return (FALSE);
	}
	return (TRUE);
}

uint32_t	get_hashed_name(t_preparse *prep, char *name)
{
	int			max_rooms;
	uint32_t	hashed_name;

	max_rooms = 0;
	hashed_name = jenkins_hash(name);
	while (prep->hashed_rooms[hashed_name].name && ++max_rooms)
	{
		if (prep->hashed_rooms[hashed_name].name &&
					ft_strcmp(prep->hashed_rooms[hashed_name].name, name) == 0)
			return (FALSE);
		hashed_name = (hashed_name < PRIME - 1) ? hashed_name += 1 : 1;
		if (max_rooms > PRIME)
			return (FALSE);
	}
	return (hashed_name);
}
