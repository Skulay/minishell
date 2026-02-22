/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alehamad <alehamad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/22 17:41:21 by alehamad          #+#    #+#             */
/*   Updated: 2026/02/22 19:55:50 by alehamad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	export_error(char *arg)
{
	write(2, "minishell: export: `", 21);
	write(2, arg, ft_strlen(arg));
	write(2, "': not a valid identifier\n", 26);
}

int	valid_identifier(char *str)
{
	int	i;

	if (!str || str[0] == '=')
		return (0);
	if (!ft_isalpha(str[0]) && str[0] != '_')
		return (0);
	i = 1;
	while (str[i] && str[i] != '=')
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

int	ft_export(t_data *data, char **args)
{
	int i;
	int status;

	status = 0;
	if (!args[1])
		return (ft_export_no_arg(data));
	i = 1;
	while (args[i])
	{
		if (!valid_identifier(args[i]))
		{
			export_error(args[i]);
			status = 1;
		}
		else
			add_update_env(data, args[i]);
		i++;
	}
	return (status);
}
