/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredocs.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alehamad <alehamad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/02 03:53:22 by tkhider           #+#    #+#             */
/*   Updated: 2026/03/03 17:40:46 by alehamad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

char	*ft_heredoc_expand(char *line)
{
	char	*new_line;
	char	*value;
	int		len;
	int		i;

	free(line);
	return (new_line);
}

// recuperer la value a chercher

// trouver la value

// ajouter la value a une nouvelle string

// cherche la prochaine value vis a vis de la nouvelle string si il y'en a une

//        TEST

// $USER test $USER test $USER
// sku test $USER test $USER
// sku test sku test $USER
// sku test sku test sku

//        TEST2

// test$USERufhrehu
// test

//        TEST3

// test $USERufhrehu
// test

//        TEST4

// test $USER ufhrehu
// test sku ufhrehu

//        TEST5

// test $USER$USER
// test skusku

//        TEST6

// test $USER$PWDEW
// test sku

//        TEST7

// test $USER$PWDEW salut
// test sku salut

// test $USERFEWFWE$PWD salut
// test /home/sku/projet/minishell salut

// donc faire un tableaux split sur espace
// a chaque tab[i] si c'est une var l'expand et si on trouve pas return le debut du tableaux
// plusieur var a la suite sont accepter

// renvoyer la nouvelle string
