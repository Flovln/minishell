/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fviolin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/29 10:34:00 by fviolin           #+#    #+#             */
/*   Updated: 2016/03/13 16:53:07 by fviolin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
 * * Function for splitting PATH string and save Paths as double array
 */

char	**split_path(char **env, char **cmd)
{
	char	*path_str_cpy;
	char	**path;
	int		cmd_nb;

	path_str_cpy = NULL;
	path = NULL;
	cmd_nb = ft_tablen(cmd);
	if (cmd_nb)
	{
		path_str_cpy = get_env_content(env, "PATH");
		if (path_str_cpy)
			path = ft_strsplit(path_str_cpy, ':');
		else
			path = NULL;
		return (path);
	}
	else
		return (NULL);
}

/*
 * * Function command managing
 */

void	exe_cmd(char **env, char **cmd, char *cmd_path)
{
	char	*tmp;
	pid_t	pid;

	pid = fork();
	if (pid > 0) // father waits for his child process to be done to exit
		wait(0);
	else if (pid == 0) // child
	{
		tmp = ft_strjoin(cmd_path, "/");
		ft_strdel(&cmd_path);
		cmd_path = ft_strjoin(tmp, cmd[0]);
		ft_strdel(&tmp);
		execve(cmd_path, cmd, env);
	}
	else
		ft_putendl("exe_cmd() error");
}

/*
 * * Function getting cmd path
 */ 

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
	ft_putendl("could not find cmd path");
	return (NULL);
}

int		main(int ac, char **av, char **env)
{
	char	**env_cpy;
	char	*line;
	char	**cmd;
	char	**path_cpy;
	char	*cmd_path; //

	cmd_path = NULL; //
	env_cpy = NULL;
	av = NULL;
	env_cpy = tab_dup(env);
	if (ac == 1)
	{
		while (1)
		{
			prompt(env_cpy);
			if (get_next_line(0, &line) == 1)
			{
				/* get commands enter through stdin in prompt and save them in **cmd */
				cmd = ft_strsplit(line, ' ');
				ft_strdel(&line);
				path_cpy = split_path(env, cmd);
			}
			if (!(ft_strcmp(cmd[0], "exit")) && ft_tablen(cmd) == 1)
			{
				printf("env_cpy freed -> |%s|\n", *env_cpy);
				ft_strdel(env_cpy);
				printf("cmd freed -> |%s|\n", *cmd);
				ft_strdel(cmd);
				printf("path_cpy freed -> |%s|\n", *path_cpy);
				ft_strdel(path_cpy);
				break ;
			}
			else
			{
				/* find and execute cmd entered through stdin */
				if ((cmd_path = get_cmd_path(cmd[0], path_cpy)) != NULL)
					exe_cmd(env, cmd, cmd_path);
				else
					ft_putendl("--- Command not found ---");
			}
		}
	}
	return (0);
}
