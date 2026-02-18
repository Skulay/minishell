/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alehamad <alehamad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/10 10:57:41 by alehamad          #+#    #+#             */
/*   Updated: 2026/02/18 13:52:10 by alehamad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	ft_pwd(t_data *data)
{
	int	i;

	i = 0;
	while (data->my_env[i])
	{
		if (ft_strncmp(data->my_env[i], "PATH=", 5) == 0)
		{
			ft_printf("%s\n", data->my_env[i]);
			return ;
		}
		i++;
	}
}
