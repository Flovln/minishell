/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setenv.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fviolin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/14 17:05:03 by fviolin           #+#    #+#             */
/*   Updated: 2016/03/15 10:53:54 by fviolin          ###   ########.fr       */
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
	new_env[i] = ft_strjoin(cmd[1], "=");
	tmp = new_env[i];
	new_env[i] = ft_strjoin(tmp, cmd[2]);
	ft_strdel(&tmp);
	new_env[i + 1] = NULL;
	//free tab env
	return(new_env);
}

/*
 * * checking if var already exists is in env
 */

int				is_include(char **env, char *cmd)
{
	int i;
	int	len;

	i = 0;
	len = ft_strlen(cmd);
	while (env && env[i])
	{
		if (!ft_strncmp(env[i], cmd, len))
			break ;
		i++;
	}
	return (i);
}

/*
 * * modify str if var already exists in env
 */

static char		**change_str(char **env, char **cmd, int i, int len)
{
	char *tmp;

	if (len == 1)
	{
		//free tab
		return (NULL);
	}
	env[i] = ft_strcat(cmd[1], "=");
	tmp = env[i];
	env[i] = ft_strjoin(tmp, cmd[2]);
	i++;
	env[i] = NULL;
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
		ft_putendl_fd("setenv takes 2 parameters", 2);
		return (env);
	}
	else
	{
		len = ft_tablen(env);
		if (( i = is_include(env, cmd[1])) == len || len == 0)
		{
			if (!(new_env = (char **)malloc(sizeof(char *) * (len + 2))))
				return (NULL);
			/* add new str in env */
			new_env = add_str(env, new_env, cmd, len);
			return (new_env);
		}
		else
		{
			new_env = change_str(env, cmd, i, len);
			return (new_env);
		}
	}
	// free tab env
	return (NULL);
}
