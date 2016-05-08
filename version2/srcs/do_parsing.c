/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_parsing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fviolin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/26 16:38:00 by fviolin           #+#    #+#             */
/*   Updated: 2016/05/01 18:00:41 by fviolin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/twtwosh.h"

char	**parse_path(t_lst *list)
{
	char *path;
	char **split_path;

	split_path = NULL;
	path = get_content(list, "PATH=");
	if (path)
	{
		split_path = ft_strsplit(path, ':');
//		ft_strdel(&path);
		return (split_path);
	}
	return (NULL);
}

void	get_exitcode(t_lst *list, char **cmd)
{
	int	i;
	int	exit_code;

	i = 0;
	exit_code = 0;
	while (cmd[1][i])
	{
		if (!ft_isdigit(cmd[1][i]))
		{
			ft_error("exit: Badly formed number.", 0);
			return ;
		}
		i++;
	}
	exit_code = ft_atoi(cmd[1]);
	//free_tab(cmd);
	list = NULL; //tmp to shut error
	//free list
	exit(exit_code);
}

void	do_exit(t_lst *list, char **cmd)
{
	int len;

	len = ft_tablen(cmd);
	if (len == 1)
	{
		//free_tab(cmd);
		list = NULL; //tmp to shut error
		//free list
		exit(0);
	}
	else if (len == 2)
		get_exitcode(list, cmd);
	else
		ft_error("exit: Expression Syntax.", 0);
}

void	parse_cmd(t_lst *list, char **cmd, char *str)
{
	char **paths;

	cmd = ft_strsplit_ws(str);
	//	ft_strdel(&str);
	paths = parse_path(list);
	if (ft_tablen(cmd))
	{
		if (!(ft_strcmp(cmd[0], "exit")))
			do_exit(list, cmd);
		manage_cmd(list, cmd, paths);
	}
}
