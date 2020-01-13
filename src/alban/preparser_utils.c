/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   preparser_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pauljull <pauljull@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/05 16:35:32 by aboitier          #+#    #+#             */
/*   Updated: 2019/12/21 09:00:15 by pauljull         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/lem_in.h"
#include <stdlib.h>

char			*ft_strcsub(char *s, char c)
{
	char	*new;
	int		i;
	int		j;

	new = NULL;
	i = 0;
	j = 0;
	while (s[i] && s[i] != c)
		i++;
	if (!(new = (char *)malloc(sizeof(char) * i + 1)))
		return (NULL);
	while (s[j] && j < i)
	{
		new[j] = s[j];
		j++;
	}
	new[j] = '\0';	
	return (new);
}

int				count_char_until(char *str, char c, char u)
{
	int	count;
	int i;

	count = 0;
	i = 0;
	while (str[i] && str[i] != u)
	{
		if (str[i] == c)
			count++;
		i++;
	}
	return (count);
}
