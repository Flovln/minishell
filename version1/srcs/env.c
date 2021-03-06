/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fviolin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/15 10:54:59 by fviolin           #+#    #+#             */
/*   Updated: 2016/03/22 19:02:31 by fviolin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static char		**unset_opt(char **env, char **cmd, char **tmp)
{
	int	len;

	len = ft_tablen(cmd);
	if (len == 2)
		ft_putendl_fd("error: too few arguments", 2);
	else if (len == 3)
		return (do_unsetenv(env, ++cmd, 1));
	else if (len > 3)
	{
		tmp = do_unsetenv(tmp, &cmd[1], 1);
		fork_redirection(tmp, cmd, 3);
	}
	return (env);
}

static char		**ignore_opt(char **env, char **cmd, char **tmp)
{
	int len;

	len = ft_tablen(cmd);
	if (len == 2)
	{
		free_tab(tmp);
		return (env);
	}
	else if (len > 2)
		fork_redirection(NULL, cmd, 2);
//	free_tab(tmp); free error
	return (env);
}

static char		**equal_opt(char **env, char **cmd, char **tmp)
{
	int len;

	len = ft_tablen(cmd);
	if (len == 2)
	{
		free_tab(tmp);
		env = setenv_redirection(env, cmd);
		return (env);
	}
	else if (len > 2)
	{
		tmp = setenv_redirection(tmp, cmd);
		fork_redirection(tmp, cmd, 2);
	}
	free_tab(tmp);
	return (env);
}

static char		**manage_env_opt(char **env, char **cmd)
{
	int len;

	len = ft_tablen(cmd);
	if (len > 1)
		fork_redirection(env, cmd, 1);
	return (env);
}

char			**manage_do_env(char **env, char **cmd, char **tmp)
{
	if (!ft_strcmp(cmd[1], "-u") || !ft_strcmp(cmd[1], "--unset"))
		return (unset_opt(env, cmd, tmp));
	else if ((!ft_strcmp(cmd[1], "-i") || !ft_strcmp(cmd[1], "-") ||
				!ft_strcmp(cmd[1], "--ignore-environment")))
		return (ignore_opt(env, cmd, tmp));
	else if ((ft_occ_nb(cmd[1], '=') == 1))
		return (equal_opt(env, cmd, tmp));
	else if (!ft_strcmp(cmd[1], "--version"))
		ft_putendl_fd("-- version 1.0 created by fviolin", 2);
	else if (cmd[1])
		return (manage_env_opt(env, cmd));
	return (env);
}
