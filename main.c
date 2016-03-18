/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fviolin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/29 10:34:00 by fviolin           #+#    #+#             */
/*   Updated: 2016/03/18 10:47:53 by fviolin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
 * * Function parsing PATH string
 */

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

/*
 * * Function -> parse cmd entered as arguments / GNL / builtin + cmd control
 */

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
	free_tab(cmd);
	return (env);
}

static char		**parse_cmd(char **env, char **cmd, char *line, char **path)
{
	cmd = ft_strsplit(line, ' '); // gerer isspace
	ft_strdel(&line);
	path = parse_path(env);
	if (ft_tablen(cmd))
	{
		if (!(ft_strcmp(cmd[0], "exit")) && ft_tablen(cmd) == 1)
		{
			if (env && cmd && path)
				free_ptrs(env, cmd, path);
			exit (0);
		}
		env = manage_cmd(env, cmd, path);
	}
	return (env);
}

static void		manage_stdin(char **env, char **path)
{
	int		i;
	char	*line;
	char	**cmd;

	cmd = NULL;
	line = NULL;
	while (1)
	{
		prompt(env);
		if (get_next_line(0, &line) == 1)
		{
			i = -1;
			cmd = ft_strsplit(line, ';');
			ft_strdel(&line);
			while (cmd[++i])
				env = parse_cmd(env, cmd, cmd[i], path);
			ft_putchar('\n');
		}
		else
			ft_putendl_fd("error: wrong usage", 2);
	}
}

int				main(int ac, char **av, char **env)
{
	char	**env_cpy;
	char	**path_cpy;

	env_cpy = NULL;
	path_cpy = NULL;
	av = NULL;
	env_cpy = tab_dup(env);
	signal(SIGINT, SIG_IGN);
	if (ac == 1)
		manage_stdin(env_cpy, path_cpy);
	else
		return (1);
	return (0);
}
