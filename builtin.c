/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fviolin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/14 14:45:40 by fviolin           #+#    #+#             */
/*   Updated: 2016/03/16 10:26:24 by fviolin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
 * * Check builtin
 */

int		is_builtin(char *cmd)
{
	if (!ft_strcmp(cmd, "cd"))
		return (1);
	else if (!ft_strcmp(cmd, "setenv"))
		return (2);
	else if (!ft_strcmp(cmd, "unsetenv"))
		return (3);
	else if (!ft_strcmp(cmd, "env"))
		return (4);
	else
		return (0);
}

/*
 * * Buitin Manager
 */

char	**do_builtin(char **cmd, char **env)
{
	char	**new_env;
	int		i;

	i = 0;
	new_env = NULL;
	if (!ft_strcmp(cmd[0], "cd"))
		new_env = do_cd(cmd, env);
	else if (!ft_strcmp(cmd[0], "setenv"))
		new_env = do_setenv(env, cmd);
	else if (!ft_strcmp(cmd[0], "unsetenv"))
		new_env = do_unsetenv(env, cmd);
	else
		new_env = do_env(env, cmd);
	return (new_env);
}
