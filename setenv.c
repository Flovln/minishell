/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setenv.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fviolin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/14 17:05:03 by fviolin           #+#    #+#             */
/*   Updated: 2016/03/15 14:08:57 by fviolin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
 * * Add a new string in env
 */

char			**add_str(char **env, char **new_env, char **cmd, int len)
{
	int 	i;
	char	*tmp;

	i = 0;
	while (i < len)
	{
		new_env[i] = ft_strdup(env[i]);
		i++;
	}
	tmp = ft_strjoin(cmd[1], "=");
	new_env[i] = ft_strjoin(tmp, cmd[2]);
	ft_strdel(&tmp);
	new_env[i + 1] = NULL;
	free_tab(env);
	return(new_env);
}

/*
 * * modify str if var already exists in env
 */

static char		**update_str(char **env, char **cmd, int i, int len)
{
	char *tmp;

	if (len == 1)
	{
		free_tab(env);
		return (NULL);
	}
	ft_strdel(&env[i]);
	env[i] = ft_strcat(cmd[1], "=");
	tmp = env[i];
	env[i] = ft_strjoin(tmp, cmd[2]);
	env[i + 1] = NULL;
	return (env);
}

/*
 * * setenv command
 */

char			**do_setenv(char **env, char **cmd)
{
	int		i;
	int		len;
	char	**new_env;

	if (ft_tablen(cmd) != 3)
	{
		ft_putendl_fd("setenv requires 2 parameters", 2);
		return (env);
	}
	else
	{
		len = ft_tablen(env);
		if ((i = is_include(env, cmd[1])) == len || len == 0)
		{
			if (!(new_env = (char **)malloc(sizeof(char *) * (len + 2))))
				return (NULL);
			/* add new str in env */
			new_env = add_str(env, new_env, cmd, len);
			return (new_env);
		}
		new_env = update_str(env, cmd, i, len);
		return (new_env);
	}
	free_tab(env);
	return (NULL);
}
