/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alehamad <alehamad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/10 10:58:03 by alehamad          #+#    #+#             */
/*   Updated: 2026/02/21 12:27:33 by alehamad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

// env with no options or arguments
// diff avec export | env affiche les var avec une valeur
// export affiche toute les var meme sans valeur en ordre ASCII

int	have_value(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '=')
		i++;
	if (str[i] == '=' && str[i + 1])
		return (1);
	return (0);

}

void	ft_env(t_data *data)
{
	int	i;

	i = 0;
	while (data->my_env[i])
	{
		if (have_value(data->my_env[i]))
			ft_printf("%s\n", data->my_env[i]);
		i++;
	}
}
