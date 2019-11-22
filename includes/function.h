/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   function.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pauljull <pauljull@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/18 14:51:52 by pauljull          #+#    #+#             */
/*   Updated: 2019/11/20 14:56:34 by pauljull         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FUNCTION_H

# define FUNCTION_H

typedef int t_bool;

t_list		*ft_recover_data(void);
t_bool		ft_parsing(t_list *data, t_lem *colony);
char		*ft_passing_name(char *str);
t_bool		ft_is_comment(char *str, t_bool condition);
t_bool		ft_is_room(char *str);
t_bool		ft_is_tube(char *str);
t_bool		ft_is_numb_str(char **str);

#endif