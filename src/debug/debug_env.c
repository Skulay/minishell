/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alehamad <alehamad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/17 06:55:38 by alehamad          #+#    #+#             */
/*   Updated: 2026/02/17 06:55:58 by alehamad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	print_env(t_data *data)
{
	int	i;

	if (!data || !data->my_env)
		return;
	i = 0;
	while (data->my_env[i])
	{
		ft_putendl_fd(data->my_env[i], 1);
		i++;
	}
}
