/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parser_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pauljull <pauljull@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/19 15:14:59 by pauljull          #+#    #+#             */
/*   Updated: 2019/11/20 14:56:09 by pauljull         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

t_bool		ft_is_numb_str(char **str)
{
	char	*s_tmp;
	char	*s_ref;
	
	s_tmp = *str;
	if (s_tmp[0] == '-')
		s_ref = "-2147483648";
	else
		s_ref = "2147483647";
	if (ft_strlen(s_tmp) < ft_strlen(s_ref))
	{
		*str += ft_strclen(*str, ' ');
		return (TRUE);
	}
	while (*s_tmp)
	{
		if (*s_tmp > *s_ref)
			return (FALSE);
		else if (*s_tmp < *s_ref)
			return (TRUE);
		s_tmp += 1;
		s_ref += 1;
	}
	*str = s_tmp;
	return (TRUE);
}

char	*ft_passing_name(char *str)
{
	while (*str != 0 && *str != '\n' && ft_is_whitespace(*str) == FALSE
	&& *str != '-')
		str += 1;
	return (str);
}

t_bool	ft_is_comment(char *str, t_bool condition)
{
	if (str[0] == '#')
	{
		if ((ft_strcmp(str, "##start") == 0 || ft_strcmp(str, "##end") == 0)
		&& condition == FALSE)
			return (FALSE);
		return (TRUE);
	}
	return (FALSE);
}

t_bool	ft_is_room(char *str)
{
	if (*str != 0 && *str != '\n' && ft_is_whitespace(*str) == FALSE
	&& *str != '-')
		str = ft_passing_name(str);
	else
		return (FALSE);
	if (*(str++) != ' ')
		return (FALSE);
	if (ft_is_numb_str(&str) == FALSE)
		return (FALSE);
	if (*(str++) != ' ')
		return (FALSE);
	if (ft_is_numb_str(&str) == FALSE)
		return (FALSE);
	if (*str != 0)
		return (FALSE);
	return (TRUE);
}

t_bool	ft_is_tube(char *str)
{
	if (*str != 0 && *str != '\n' && ft_is_whitespace(*str) == FALSE
	&& *str != '-')
		str = ft_passing_name(str);
	else
		return (FALSE);
	if (*(str++) != '-')
		return (FALSE);
	str = ft_passing_name(str);
	if (*str != 0)
		return (FALSE);
	return (TRUE);
}
