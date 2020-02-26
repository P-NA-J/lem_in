/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pauljull <pauljull@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/18 14:33:58 by pauljull          #+#    #+#             */
/*   Updated: 2020/02/25 15:22:12 by aboitier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/lem_in.h"
#include <stdlib.h>

int			get_nb_ants(t_map *data, t_preparse *prep, int i)
{
	long	ants_nb;
	char	*nb_ants;
	int		len;

	nb_ants = NULL;
	if ((nb_ants = ft_strcsub(prep->buffer - i, '\n')) == NULL)
		return (FALSE);
	len = ft_strlen(nb_ants);
	if ((len == 10 && (nb_ants[0] != '1' && nb_ants[0] != '2')) || len > 10)
		return (FALSE);
	data->preparse->buffer += ft_strclen(prep->buffer, '\n') + 1;
	ants_nb = ft_atol(nb_ants);
	if (ants_nb > INT_MAX)
		return (FALSE);
	free(nb_ants);
	return ((int)ants_nb);
}

int			parse_nb_ants(t_map *data, t_preparse *prep)
{
	int		i;

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
	return (get_nb_ants(data, prep, i));
}

int			check_if_start_or_end(t_preparse *prep, t_map *data, char *tmp)
{
	int retour;

	retour = TRUE;
	if (ft_strcmp((const char *)tmp, "##start") == 0)
	{
		if (data->start)
			retour = FALSE;
		prep->s_or_e = 1;
	}
	else if (ft_strcmp((const char *)tmp, "##end") == 0)
	{
		if (data->end)
			retour = FALSE;
		prep->s_or_e = 2;
	}
	free(tmp);
	return (retour);
}

int			parse_comment(t_preparse *prep, t_map *data)
{
	int		size;
	char	*tmp;

	tmp = NULL;
	if (prep->buffer[1] && prep->buffer[1] == '#')
	{
		if (prep->s_or_e)
			return (FALSE);
		if (!(tmp = ft_strcsub(prep->buffer, '\n')))
			return (FALSE);
		size = ft_strlen(tmp);
		prep->buffer += size + 1;
		if (check_if_start_or_end(prep, data, tmp) == FALSE)
			return (FALSE);
	}
	else
		prep->buffer += ft_strclen(prep->buffer, '\n') + 1;
	return (get_next_room(prep, data));
}

t_map		*parser(void)
{
	t_map		*data;

	if (!(data = (t_map *)malloc(sizeof(t_map))))
		return (NULL);
	ft_bzero(data, sizeof(t_map));
	if ((data->preparse = pre_parser()) == NULL)
		return (which_error(data, 2));
	data->preparse->hashed_rooms[0].name = "Not Empty";
	data->preparse->tmp_buff = data->preparse->buffer;
	if ((data->nb_ants = parse_nb_ants(data, data->preparse)) == FALSE)
		return (which_error(data, 2));
	if ((data->rooms = get_rooms(data, data->preparse)) == NULL)
		return (which_error(data, 2));
	if (parse_rooms(&data, data->preparse) == FALSE)
		return (which_error(data, 2));
	if (data->start == NULL || data->end == NULL)
		return (which_error(data, 2));
	if (get_pipes(&data, data->preparse) == FALSE)
		return (which_error(data, 1));
	return (data);
}
