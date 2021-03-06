/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_digit.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pauljull <pauljull@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/30 16:27:27 by pauljull          #+#    #+#             */
/*   Updated: 2019/10/30 16:27:38 by pauljull         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

int			ft_digit(long nb)
{
	int				i;

	i = 1;
	if (nb < 0)
	{
		i += 1;
		return (i + ft_digit(-(nb / 10)));
	}
	if ((nb / 10) > 0)
		return (1 + ft_digit(nb / 10));
	return (1);
}
