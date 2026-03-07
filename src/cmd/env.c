/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkhider <tkhider@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/10 10:58:03 by alehamad          #+#    #+#             */
/*   Updated: 2026/03/08 00:46:35 by tkhider          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	ft_env(t_data *data)
{
	int	i;

	i = 0;
	while (data->my_env[i])
	{
		if (ft_strchr(data->my_env[i], '='))
			ft_printf("%s\n", data->my_env[i]);
		i++;
	}
	return (0);
}
