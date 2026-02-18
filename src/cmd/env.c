/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alehamad <alehamad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/10 10:58:03 by alehamad          #+#    #+#             */
/*   Updated: 2026/02/18 02:48:09 by alehamad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

// env with no options or arguments

void	ft_env(t_data *data)
{
	int	i;

	i = 0;
	while (data->my_env[i])
	{
		ft_printf("%s\n", data->my_env[i]);
		i++;
	}
}
