/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   macro.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pauljull <pauljull@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/18 14:39:42 by pauljull          #+#    #+#             */
/*   Updated: 2019/12/16 03:40:34 by pauljull         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MACRO_H

# define MACRO_H

# define BUFF_SIZE 		4096
# define IGNORE 		-1
# define PRIME 			36131
# define EMPTY			3
# define RESTRICT		4
# define FULL			5
/*
** Errors
*/ 

# define ERR_BAD_DATA	-2

/*
** Features
*/ 

# define VISITED 					00000001
# define END_CONNECT 				00000010
# define OCCUPIED 					00000100
# define ENTRY 						00001000
# define ADDED_NEIGHBORS			00010000
# define IS_START					00100000
# define IS_END						01000000
# define UNCHANGED					1
# define UNQUEUE					2
# define AUGMENTED					3
# define INF						4
# define BLOCKED					5
# define QUEUE						9
# define CUT 			00000001
# define AUG_VISITED                11
# define AUG_START                  12
# define COUCOU printf("coucou\n")

/*
**	Colors
*/ 

#  define _RED      "\x1b[31m"
#  define _GREEN    "\x1b[32m"
#  define _YELLOW   "\x1b[33m"
#  define _BLUE     "\x1b[34m"
#  define _MAGENTA  "\x1b[35m"
#  define _CYAN     "\x1b[36m"
#  define _RESET    "\x1b[0m"




#endif
