/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fviolin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/15 10:54:59 by fviolin           #+#    #+#             */
/*   Updated: 2016/03/15 11:36:16 by fviolin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_env(char **env)
{
	if (env && *env)
	{
		while (*env)
		{
			ft_putendl(*env);
			env++;
		}
	}
	else
		ft_putendl_fd("empty environment - print_env()", 2);
}

char	**do_env(char **env, char **cmd)
{
	char	**tmp;

	tmp = NULL;
	if (ft_tablen(cmd) == 1)
	{
		print_env(env);
		return (env);
	}
	if (env)
		tmp = tab_dup(env);
	return (env);
}
