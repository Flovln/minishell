/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fviolin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/15 10:54:59 by fviolin           #+#    #+#             */
/*   Updated: 2016/03/17 13:32:58 by fviolin          ###   ########.fr       */
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
		return (do_unsetenv(env, ++cmd)); // cmd[1]
	else if (len > 3)
	{
		tmp = do_unsetenv(tmp, &cmd[1]);
		fork_redirection(tmp, cmd, 3);
	}
	free_tab(tmp);
	return (tmp);
}

static char		**ignore_opt(char **env, char **cmd, char **tmp)
{
	int len;

	len = ft_tablen(cmd);
	if (len == 2)
	{
		free_tab(tmp);
		env = ignore_env(env, len);
		return (env);
	}
	else if (len > 2)
		fork_redirection(NULL, cmd, 2);
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
		//return (setenv_redirection(env, cmd));
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

void			print_env(char **env)
{
	if (env && *env)
		while (*env)
		{
			ft_putendl(*env);
			env++;
		}
	else
		ft_putendl_fd("empty environment", 2);
}

char			**manage_do_env(char **env, char **cmd, char **tmp)
{
	/* TEST */
	printf("\n----> manage_do_env <----\n");
	printf("\ncmd[1] -> |%s|\n\n", cmd[1]);
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
