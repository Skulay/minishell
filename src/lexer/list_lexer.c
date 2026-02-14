/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_lexer.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alehamad <alehamad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/11 11:03:45 by alehamad          #+#    #+#             */
/*   Updated: 2026/02/14 18:31:11 by alehamad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

t_token	*ft_toknew(char *content, t_type token_type)
{
	t_token	*lst;

	lst = malloc(sizeof(t_token));
	if (!lst)
		return (0);
	lst->value = content;
	lst->type = token_type;
	lst->next = NULL;
	return (lst);
}

t_token	*ft_toklast(t_token *lst)
{
	t_token	*i;

	if (!lst)
		return (0);
	i = lst;
	while (i->next)
		i = i->next;
	return (i);
}

void	ft_tokadd_back(t_token **lst, t_token *new)
{
	t_token	*last;

	if (!lst || !new)
		return ;
	if (!*lst)
	{
		*lst = new;
		return ;
	}
	last = ft_toklast(*lst);
	last->next = new;
}


