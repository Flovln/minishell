/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fviolin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/29 10:34:00 by fviolin           #+#    #+#             */
/*   Updated: 2016/03/15 09:08:45 by fviolin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
 * * Function parsing PATH string
 */

char	**parse_path(char **env, char **cmd)
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

void	free_ptr(char **env_cpy, char **cmd, char **path_cpy)
{
	ft_strdel(env_cpy);
	ft_strdel(cmd);
	ft_strdel(path_cpy);
}

int		main(int ac, char **av, char **env)
{
	char	**env_cpy;
	char	*line;
	char	**parse_cmd;
	char	**path_cpy;

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
				/* parse commands entered through stdin and save them in **cmd */
				parse_cmd = ft_strsplit(line, ' ');
				ft_strdel(&line);
				path_cpy = parse_path(env_cpy, parse_cmd);
			}
			if (!(ft_strcmp(parse_cmd[0], "exit")) && ft_tablen(parse_cmd) == 1)
			{
				free_ptr(env_cpy, parse_cmd, path_cpy);
				break ;
			}
			else if (is_builtin(parse_cmd[0]) > 0)
				env_cpy = do_builtin(parse_cmd, env_cpy);
			else
				exe_cmd(env, parse_cmd, path_cpy);
		}
	}
	return (0);
}
