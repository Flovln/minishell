/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fviolin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/14 11:33:17 by fviolin           #+#    #+#             */
/*   Updated: 2016/03/16 10:57:02 by fviolin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
 * * Get commands paths
 */
/* open and read each dir saved in **path until cmd saved in *cmd matches */

char	*get_cmd_path(char *cmd, char **path)
{
	int				i;
	int				j;
	DIR				*dir;
	struct dirent	*ret;

	if (cmd && path)
	{
		i = 0;
		j = 0;
		while (path[i])
		{
			if ((dir = opendir(path[i])))
				while ((ret = readdir(dir)))
					if (!ft_strcmp(ret->d_name, cmd))
					{
						closedir(dir);
						return (ft_strdup(path[i]));
					}
			closedir(dir);
			i++;
		}
	}
	ft_putstr_fd("minishell: command not found: ", 2);
	ft_putendl_fd(cmd, 2);
	return (NULL);
}

/*
 * * Command managing takes **env / parse cmd / parse path cpy
 */

void	exe_cmd(char **env, char **cmd, char **path)
{
	char	*cmd_path;
	char	*tmp;
	pid_t	pid;

	cmd_path = NULL;
	if ((cmd_path = get_cmd_path(cmd[0], path)) != NULL)
	{	
		pid = fork();
		if (pid > 0) // father
			wait(0);
		else if (pid == 0) // child
		{
			tmp = ft_strjoin(cmd_path, "/");
			ft_strdel(&cmd_path);
			cmd_path = ft_strjoin(tmp, cmd[0]);
			ft_strdel(&tmp);
			execve(cmd_path, cmd, env);
		}
	}
}
