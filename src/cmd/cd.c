/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alehamad <alehamad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/10 10:57:26 by alehamad          #+#    #+#             */
/*   Updated: 2026/02/19 00:29:16 by alehamad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

// ne pas oublier de modifier le PWD et le OLD PWD dans l'env

void	ft_cd(t_data *data, char *str)
{
	chdir(str);
}
