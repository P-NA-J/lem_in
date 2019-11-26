/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parsing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pauljull <pauljull@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/19 11:33:16 by pauljull          #+#    #+#             */
/*   Updated: 2019/11/25 19:22:16 by pauljull         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

static t_bool	ft_tube_check(t_list **data)
{
	t_list	*tmp;

	tmp = *data;
	while (tmp != NULL && (ft_is_comment(tmp->content, FALSE) == TRUE ||
	ft_is_tube(tmp->content) == TRUE))
	{
		if (ft_is_room(tmp->content) == TRUE)
			return (FALSE);
		tmp = tmp->next;
	}
	*data = tmp;
	if (tmp != NULL)
		return (FALSE);
	return (TRUE);
}

static t_bool	ft_room_definition_check(t_list **data, t_map *galery)
{
	size_t	start;
	size_t	end;
	t_list	*tmp;

	tmp = *data;
	start = 0;
	end = 0;
	while (tmp != NULL && (ft_is_comment(tmp->content, TRUE) == TRUE
	|| ft_is_room(tmp->content) == TRUE))
	{
		if (ft_strcmp(tmp->content, "##start") == 0)
			start += 1;
		else if (ft_strcmp(tmp->content, "##end") == 0)
			end += 1;
//		else if (ft_is_room(tmp->content) == TRUE)
//			colony->room += 1;
		tmp = tmp->next;
	}
	*data = tmp;
	if (start == 1 && end == 1)
		return (TRUE);
	return (FALSE);
}

t_bool	ft_parsing(t_list *data, t_map *galery)
{	
	while (data != NULL && ft_is_comment(data->content, FALSE) == TRUE)
		data = data->next;
	if (ft_is_numb_str(&(data->content)) == TRUE)
	{
		galery->nb_ants = ft_atoi(data->content);
		data = data->next;
	}
	else
		return (FALSE);
	if (ft_room_definition_check(&data, galery) == FALSE)
		return (FALSE);
	if (ft_tube_check(&data) == FALSE)
		return (FALSE);
	if (data != NULL)
		return (FALSE);
	return (TRUE);
}