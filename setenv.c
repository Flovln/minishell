/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setenv.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fviolin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/14 17:05:03 by fviolin           #+#    #+#             */
/*   Updated: 2016/03/17 12:06:54 by fviolin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
 * * redirection for env <var name>=<content>
 */

char			**setenv_redirection(char **env, char **cmd)
{
	char	*tab[4];
	char	**new_env;
	printf(" --- setenv_redirection ---\n");
	tab[0] = ft_strdup("setenv");
	printf("tab[0] -> |%s|\n", tab[0]);
	tab[1] = ft_strcdup(cmd[1], '=');
	printf("tab[1] -> |%s|\n", tab[1]);
	tab[2] = ft_strsub(ft_strstr(cmd[1], "="), 1, ft_strlen(cmd[1])
			- ft_strlen(tab[0]) + 3);
	printf("tab[2] -> |%s|\n", tab[2]);
	tab[3] = NULL;
	printf("tab[3] -> |%s|\n", tab[3]);
	new_env = do_setenv(tab, env);
	ft_strdel(&tab[0]);
	ft_strdel(&tab[1]);
	ft_strdel(&tab[2]);
	return (new_env);
}

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
		ft_putendl_fd("setenv: too few arguments", 2);
		return (env);
	}
	else
	{
		len = ft_tablen(env);
		if ((i = is_include(env, cmd[1])) == len || len == 0)
		{
			if (!(new_env = (char **)malloc(sizeof(char *) * (len + 2))))
				return (NULL);
			new_env = add_str(env, new_env, cmd, len);
			free_tab(env);
			return (new_env);
		}
		return (update_str(env, cmd, i, len));
		//new_env = update_str(env, cmd, i, len);
		//return (new_env);
	}
	return (NULL);
}
