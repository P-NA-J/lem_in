/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   jenkins_hash.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pauljull <pauljull@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/02 20:19:49 by aboitier          #+#    #+#             */
/*   Updated: 2020/02/24 20:56:37 by aboitier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/lem_in.h"

uint32_t	jenkins_hash(char *name)
{
	size_t		i;
	uint32_t	hash;

	i = 0;
	hash = 0;
	while (name[i] != '\0')
	{
		hash += name[i];
		hash += (hash << 10);
		hash ^= (hash >> 6);
		i++;
	}
	hash += (hash << 3);
	hash ^= (hash >> 11);
	hash += (hash << 15);
	hash = hash % PRIME;
	return (hash);
}

int			isinchar(char *str, char c)
{
	int i;

	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			return (TRUE);
		i++;
	}
	return (FALSE);
}

int			get_hashes_rs(t_preparse *prep)
{
	if (isinchar(prep->buffer, '\n') == FALSE)
		return (FALSE);
	if (!(prep->r1 = ft_strcsub(prep->buffer, '-')))
		return (FALSE);
	prep->buffer += ft_strlen(prep->r1) + 1;
	if (!(prep->r2 = ft_strcsub(prep->buffer, '\n')))
	{
		free(prep->r1);
		return (FALSE);
	}
	prep->buffer += ft_strlen(prep->r2) + 1;
	prep->h_r1 = jenkins_hash(prep->r1);
	prep->h_r2 = jenkins_hash(prep->r2);
	return (TRUE);
}

int			compare_names(char *to_connect,
				uint32_t *h_rx, t_preparse *prep)
{
	int diff;

	diff = 0;
	while (ft_strcmp(prep->hashed_rooms[*h_rx].name,
					to_connect) != 0 && diff++ < 31)
	{
		*h_rx = (*h_rx < PRIME - 1) ? *h_rx += 1 : 1;
		if (diff == 30)
			return (FALSE);
	}
	return (TRUE);
}
