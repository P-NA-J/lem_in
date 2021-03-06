/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atol_move.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pauljull <pauljull@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/18 10:31:18 by pauljull          #+#    #+#             */
/*   Updated: 2019/10/18 22:06:19 by pauljull         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

long	ft_atol_move(char **s_ref)
{
	long	atoi;
	char	sign;
	char	*str;

	str = *s_ref;
	atoi = 0;
	sign = 1;
	while (*str == ' ' || *str == '\f' || *str == '\t'
	|| *str == '\n' || *str == '\r' || *str == '\v')
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			sign = -1;
		str++;
	}
	while (*str >= '0' && *str <= '9')
	{
		atoi = (atoi * 10) + (*str - '0');
		str++;
	}
	*s_ref = str;
	return (atoi * sign);
}
