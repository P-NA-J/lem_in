/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   jenkins_hash.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pauljull <pauljull@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/02 20:19:49 by aboitier          #+#    #+#             */
/*   Updated: 2019/12/21 09:00:13 by pauljull         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/lem_in.h"

uint32_t	jenkins_hash(char *name)
{
	size_t	i;
	uint32_t 	hash;

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
