/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fviolin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/15 17:01:38 by fviolin           #+#    #+#             */
/*   Updated: 2016/03/15 17:14:50 by fviolin          ###   ########.fr       */
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

char	**do_cd(char **cmd, char **env)
{
	DIR *dir;

	dir = NULL;
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
