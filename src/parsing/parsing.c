/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alehamad <alehamad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/10 10:54:48 by alehamad          #+#    #+#             */
/*   Updated: 2026/02/16 02:44:03 by alehamad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	parsing(t_token *token)
{
	if (!token)
		return (0);
	if (!check_error(token))
		return (0);
	if (!check_tok(token))
		return (0);
	return(1);
}

