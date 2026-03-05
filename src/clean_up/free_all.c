/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_all.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alehamad <alehamad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/05 14:49:33 by alehamad          #+#    #+#             */
/*   Updated: 2026/03/05 17:56:49 by alehamad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	free_all(t_cmd *cmd, t_data *data)
{
	if (cmd)
		free_cmd(cmd);
	if (data)
		free_data(data);
}
