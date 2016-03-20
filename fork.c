/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fviolin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/20 12:55:37 by fviolin           #+#    #+#             */
/*   Updated: 2016/03/20 14:49:33 by fviolin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**resize_cmd(char **cmd, char **cmd_tmp, int flag)
{
	int i;

	i = 0;
	while (cmd[flag])
	{
		cmd_tmp[i] = ft_strdup(cmd[flag]);
		flag++;
		i++;
	}
	cmd_tmp[i] = NULL;
	return (cmd_tmp);
}

void	fork_redirection(char **env, char **cmd, int flag)
{
	char *cmd_path;
	char *path_str;
	char **path;
	char **cmd_tmp;

	cmd_path = NULL;
	if (!(cmd_tmp = (char **)malloc(sizeof(char *) *
					(ft_tablen(cmd) - flag + 1))))
		return ;
	path_str = get_env_content(env, "PATH");
	path = ft_strsplit(path_str, ':');
	if ((cmd_tmp = resize_cmd(cmd, cmd_tmp, flag)) && env)
	{
		if (path_str && path)
		{
			cmd_path = get_cmd_path(cmd_tmp[0], path);
			if (path && cmd_path)
				exe_fork(env, cmd_tmp, cmd_path);
			else
				free_fork(cmd_tmp, path, cmd_path, path_str);
		}
	}
}
