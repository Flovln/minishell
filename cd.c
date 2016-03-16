/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fviolin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/15 17:01:38 by fviolin           #+#    #+#             */
/*   Updated: 2016/03/16 10:28:14 by fviolin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void		no_arg(char **env)
{
	char *home;

	home = NULL;
	if (env && *env)
	{
		home = get_env_content(env, "HOME");
		if (home)
		{
			chdir(home);
			ft_strdel(&home);
		}
	}
}

static void		manage_error(char **cmd)
{
	struct stat	st;

	if (stat(cmd[1], &st) == -1)
	{
		ft_putstr_fd("cd: No such file or directory: ", 2);
		ft_putendl_fd(cmd[1], 2);
	}
	else if (!(S_ISDIR(st.st_mode)))
	{
		ft_putstr_fd("cd: Not a directory: ", 2);
		ft_putendl_fd(cmd[1], 2);
	}
	else if (access(cmd[1], X_OK) == -1)
	{
		ft_putstr_fd("cd: Permission denied: ", 2);
		ft_putendl_fd(cmd[1], 2);
	}
	else
		chdir(cmd[1]);
}

static char		*user_root(char **env, char *cmd)
{
	char *home;
	char *tmp;
	char *cmd_cpy;

	cmd_cpy = NULL;
	home = get_env_content(env, "HOME");
	if (!cmd[1])
	{
		ft_strdel(&cmd);
		return (home);
	}
	if (home)
	{
		tmp = ft_strstr(cmd, "/");
		if (!(cmd_cpy = (char *)malloc(sizeof(char) *
			(ft_strlen(home) + ft_strlen(cmd) + 1))))
			return (NULL);
		cmd_cpy = ft_strcpy(cmd_cpy, home);
		cmd_cpy = ft_strcat(cmd_cpy, tmp);
		ft_strdel(&home);
		ft_strdel(&cmd);
		return (cmd_cpy);
	}
	return (NULL);
}

char			**do_cd(char **cmd, char **env)
{
	DIR *dir;

	dir = NULL;
	if (cmd[1] && cmd[1][0] == '~')
		cmd[1] = user_root(env, cmd[1]);
	if (cmd[1])
	{
		dir = opendir(cmd[1]);
		manage_error(cmd);
		if (dir)
			closedir(dir);
	}
	else if (!cmd[1])
		no_arg(env);
	return (env);
}
