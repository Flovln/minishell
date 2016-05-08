/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_fork.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fviolin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/26 16:58:14 by fviolin           #+#    #+#             */
/*   Updated: 2016/05/01 18:00:30 by fviolin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/twtwosh.h"

char	*add_full_path(char **cmd, char *cmd_path)
{
	char *tmp;

	tmp = NULL;
	if (cmd_path)
		tmp = ft_strjoin(cmd_path, "/");
	else
		tmp = ft_strdup("./");
	cmd_path = ft_strjoin(tmp, cmd[0]);
//	ft_strdel(&tmp);
	return (cmd_path);
}

void	do_fork(t_lst *list, char **cmd, char *cmd_path)
{
	pid_t	pid;
	char	**env_cpy;

	env_cpy = list_in_tab(list);
	cmd_path = add_full_path(cmd, cmd_path);
	if (access(cmd_path, X_OK) != -1)
	{
		pid = fork();
		if (pid > 0)
			wait(0);
		else if (pid == 0)
		{
			signal(SIGINT, SIG_DFL);
//			ft_strdel(&cmd_path);
			execve(cmd_path, cmd, env_cpy);
		}
	}
	else
		permissions_error_handl(list, cmd);
}
