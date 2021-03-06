/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strclen.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pauljull <pauljull@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/27 09:05:15 by pauljull          #+#    #+#             */
/*   Updated: 2019/11/13 19:03:31 by pauljull         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

size_t	ft_strclen(char *str, char c)
{
	size_t	i;

	i = 0;
	while (str[i] != 0 && str[i] != c)
		i += 1;
	return (i);
}
