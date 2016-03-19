/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fviolin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/15 10:54:59 by fviolin           #+#    #+#             */
/*   Updated: 2016/03/19 18:37:28 by fviolin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char		**unset_opt(char **env, char **cmd, char **tmp)
{
	int	len;

	len = ft_tablen(cmd);
	if (len == 2)
		ft_putendl_fd("error: too few arguments", 2);
	else if (len == 3)
		return (do_unsetenv(env, ++cmd));
	else if (len > 3)
	{
		tmp = do_unsetenv(tmp, &cmd[1]);
		fork_redirection(tmp, cmd, 3);
	}
	return (env); // ou (tmp) si on veut avoir un envir modifie
}

static char		**ignore_opt(char **env, char **cmd, char **tmp)
{
	int len;

	len = ft_tablen(cmd);
	if (len == 2)
	{
		free_tab(tmp);
		env = ignore_env(env, len); // assigne NULL a env WRONG
		return (env);
	}
	else if (len > 2) // redirige commandes qui suivent ex. env -i ls -l etc..
		fork_redirection(NULL, cmd, 2); // env instead of NULL ?
	free_tab(tmp);
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
	return (env); // (tmp)
}

char			**manage_do_env(char **env, char **cmd, char **tmp)
{
	int	flag; //

	flag = ft_tablen(cmd); //
	if (!ft_strcmp(cmd[1], "-u") || !ft_strcmp(cmd[1], "--unset"))
		return (unset_opt(env, cmd, tmp));
	else if ((!ft_strcmp(cmd[1], "-i") || !ft_strcmp(cmd[1], "-") ||
				!ft_strcmp(cmd[1], "--ignore-environment")))
		return (ignore_opt(env, cmd, tmp));
	else if ((ft_occ_nb(cmd[1], '=') == 1))
		return (equal_opt(env, cmd, tmp));
	else if (!ft_strcmp(cmd[1], "--version"))
		ft_putendl_fd("-- version 1.0 created by fviolin", 2);
	else
	{
		ft_putstr_fd("env: option not found: ", 2);
		ft_putendl_fd(cmd[1], 2);
	}
	return (env);
}

char			**do_env(char **env, char **cmd)
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
	env = manage_do_env(env, cmd, tmp);
	return (env);
}
