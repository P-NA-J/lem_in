/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pauljull <pauljull@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/18 14:33:58 by pauljull          #+#    #+#             */
/*   Updated: 2020/01/21 20:32:16 by aboitier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/lem_in.h"
#include <stdlib.h>

int				escape_comments(t_preparse *prep)
{
	int size;

	size = ft_strclen(prep->buffer, '\n');
	if (ft_strncmp((const char *)prep->buffer, "##start", size) == 0)
		return (FALSE);
	else if (ft_strncmp((const char *)prep->buffer, "##end", size) == 0)
		return (FALSE);
	prep->buffer += size + 1;
	return (TRUE);
}

int				get_nb_ants(t_map *data, t_preparse *prep)
{
	char	*nb_ants;
	int		ants_nb;
	int		i;

	nb_ants = NULL;
	i = 0;
	while (prep->buffer[0] == '#')
		if (escape_comments(prep) == FALSE)
			return (FALSE);
	if (ft_isdigit((int)*prep->buffer) == 0)
		return (FALSE);
	while (*prep->buffer && *prep->buffer != '\n')
	{
		if (ft_isdigit((int)*prep->buffer) == 0)
        	return (FALSE);
		prep->buffer++;
		i++;
	}
	if ((nb_ants = ft_strcsub(prep->buffer - i, '\n')) == NULL)
		return (FALSE);
	data->preparse->buffer += ft_strclen(prep->buffer, '\n') + 1;
	ants_nb = ft_atoi(nb_ants);
	free(nb_ants);
	return (ants_nb);
}

t_room			*parse_comment(t_preparse *prep, t_map *data)
{
	int 	size;
	char	*tmp;

	tmp = NULL;
	if (prep->buffer[1] && prep->buffer[1] == '#')
	{
		if (!(tmp = ft_strcsub(prep->buffer, '\n')))
			return (NULL);
		size = ft_strlen(tmp);
		prep->buffer = prep->buffer + size + 1;	
		if (ft_strncmp((const char *)tmp, "##start", size) == 0)
			prep->s_or_e = 1;
		else if (ft_strncmp((const char *)tmp, "##end", size) == 0)
			prep->s_or_e = 2;
		free(tmp);
	}
	else
		prep->buffer += ft_strclen(prep->buffer, '\n') + 1;
	return (get_next_room(prep, data));	
}

t_map			*parser(void)
{
	t_map		*data;

	if (!(data = (t_map *)malloc(sizeof(t_map))))
		return (NULL);
	ft_bzero(data, sizeof(t_map));
	if ((data->preparse = pre_parser()) == NULL)
		return (which_error(data, 2));
	data->preparse->hashed_rooms[0].name = "NOPE";
	data->preparse->tmp_buff = data->preparse->buffer;
	if ((data->nb_ants = get_nb_ants(data, data->preparse)) == FALSE)
		return (which_error(data, 2));
	if ((data->rooms = get_rooms(data, data->preparse)) == NULL)
		return (which_error(data, 2));
	if (data->start == NULL || data->end == NULL)
		return (which_error(data, 2));
	if (get_pipes(&data, data->preparse) == FALSE)
		return (which_error(data, 1));
	return (data);
}
