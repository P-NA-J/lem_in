/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   jenkins_hash.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboitier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/02 20:19:49 by aboitier          #+#    #+#             */
/*   Updated: 2019/12/02 21:36:06 by aboitier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>

uint32_t	jenkins_hash(char *name)
{
	size_t	i;
	uint32_t 	hash;

	i = 0;
	hash = 0;
	while (name[i])
	{
		hash += name[i];
		hash += (hash << 10);
		hash ^= (hash >> 6);
		i++;
	}
	hash += (hash << 3);
	hash ^= (hash >> 11);
	hash += (hash << 15);
	return (hash);
}

int		main()
{
	char	str[100] = "itsme";
	char	str2[100] = "1";

	//str = "its me";
	//str2 = "its ma";
	printf("%s = %u\n", str, jenkins_hash(str));
	printf("%s = %u\n", str2, jenkins_hash(str2));
	return (0);
}
