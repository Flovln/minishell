/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fviolin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/29 10:34:00 by fviolin           #+#    #+#             */
/*   Updated: 2016/03/20 15:09:36 by fviolin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char			**parse_path(char **env)
{
	char	*path_str;
	char	**split_path;

	split_path = NULL;
	path_str = get_env_content(env, "PATH");
	if (path_str)
	{
		split_path = ft_strsplit(path_str, ':');
		ft_strdel(&path_str);
		return (split_path);
	}
	return (NULL);
}

static char		**manage_cmd(char **env, char **cmd, char **path)
{
	if (is_builtin(cmd[0]) > 0)
	{
		env = do_builtin(cmd, env);
		return (env);
	}
	else
		manage_exe_cmd(env, cmd, path);
	free_tab(path);
	return (env);
}

static char		**parse_cmd(char **env, char **cmd, char *line, char **path)
{
	cmd = ft_strsplit_ws(line);
	ft_strdel(&line);
	path = parse_path(env);
	if (ft_tablen(cmd))
	{
		if (!(ft_strcmp(cmd[0], "exit")) && ft_tablen(cmd) == 1)
		{
			free_tab(env);
			free_tab(cmd);
			free_tab(path);
			exit(0);
		}
		env = manage_cmd(env, cmd, path);
	}
	return (env);
}

static void		manage_stdin(char **env, char **path, int count)
{
	int		i;
	char	*line;
	char	**cmd;

	cmd = NULL;
	line = NULL;
	while (1)
	{
		prompt(env, count);
		if (get_next_line(0, &line) == 1)
		{
			i = -1;
			cmd = ft_strsplit(line, ';');
			ft_strdel(&line);
			while (cmd[++i])
				env = parse_cmd(env, cmd, cmd[i], path);
			free(cmd);
			cmd = NULL;
			free_tab(path);
			ft_putchar('\n');
		}
		count++;
	}
	free_tab(env);
}

int				main(int ac, char **av, char **env)
{
	char	**env_cpy;
	char	**path_cpy;
	int		count;

	count = 0;
	env_cpy = NULL;
	path_cpy = NULL;
	av = NULL;
	env_cpy = tab_dup(env);
	signal(SIGINT, SIG_IGN);
	if (ac == 1)
		manage_stdin(env_cpy, path_cpy, count);
	else
		return (1);
	return (0);
}
