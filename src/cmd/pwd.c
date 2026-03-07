/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkhider <tkhider@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/10 10:57:41 by alehamad          #+#    #+#             */
/*   Updated: 2026/03/08 00:46:27 by tkhider          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	ft_pwd(t_data *data)
{
	int	i;

	i = 0;
	while (data->my_env[i])
	{
		if (ft_strncmp(data->my_env[i], "PWD=", 4) == 0)
		{
			ft_printf("%s\n", data->my_env[i] + 4);
			return (0);
		}
		i++;
	}
	return (1);
}
