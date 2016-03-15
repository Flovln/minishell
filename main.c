/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fviolin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/29 10:34:00 by fviolin           #+#    #+#             */
/*   Updated: 2016/03/15 15:50:21 by fviolin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
 * * Function parsing PATH string
 */

char			**parse_path(char **env, char **cmd)
{
	char	*path_str;
	char	**path;
	int		cmd_nb;

	path_str = NULL;
	path = NULL;
	cmd_nb = ft_tablen(cmd);
	if (cmd_nb)
	{
		path_str = get_env_content(env, "PATH");
		if (path_str)
			path = ft_strsplit(path_str, ':');
		else
			path = NULL;
		return (path);
	}
	else
		return (NULL);
}

/*
 * * FREE Function
 */

void			free_ptr(char **env_cpy, char **cmd, char **path_cpy)
{
	ft_strdel(env_cpy);
	ft_strdel(cmd);
	ft_strdel(path_cpy);
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
		exe_cmd(env, cmd, path);
	return (env);
}

static void		manage_stdin(char **env, char **cmd, char **path) //, char *line)
{
	char *line;

	line = NULL;
	while (1)
	{
		prompt(env);
		if (get_next_line(0, &line) == 1)
		{
			// parse commands entered through stdin and save them in **cmd
			cmd = ft_strsplit(line, ' ');
			ft_strdel(&line);
			path = parse_path(env, cmd);
		}
		if (ft_tablen(cmd))
		{
			if (!(ft_strcmp(cmd[0], "exit")) && ft_tablen(cmd) == 1)
			{
				free_ptr(env, cmd, path);
				break ;
			}
			env = manage_cmd(env, cmd, path);
		}
		ft_putstr("\n");
	}
}

int				main(int ac, char **av, char **env)
{
	char	**env_cpy;
	char	**cmd;
	char	**path_cpy;

	env_cpy = NULL;
	av = NULL;
	cmd = NULL;
	path_cpy = NULL;
	env_cpy = tab_dup(env);
	if (ac == 1)
		manage_stdin(env_cpy, cmd, path_cpy); //, line);
	else
		return (1);
	return (0);
}
