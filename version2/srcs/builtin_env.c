/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fviolin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/28 14:21:52 by fviolin           #+#    #+#             */
/*   Updated: 2016/05/02 09:12:55 by fviolin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/twtwosh.h"

t_lst			*create_node_cpy(t_lst *list)
{
	t_lst *new;

	if (!(new = malloc(sizeof(t_lst))))
		return (NULL);
	if (list->content)
		new->content = ft_strdup(list->content);
	new->name = ft_strdup(list->name);
	new->next = NULL;
	return (new);
}

t_lst			*do_list_cpy(t_lst *list)
{
	t_lst *new_list;

	new_list = NULL;
	while (list)
	{
		list_push_node(&new_list, create_node_cpy(list));
		list = list->next;
	}
	return (new_list);
}

int				cmd_is_in_path(char *str, char **paths)
{
	struct dirent	*ret;
	DIR				*dir;
	int				i;

	if (str && paths && *paths)
	{
		i = 0;
		while (*paths)
		{
			if ((dir = opendir(*paths)))
			{
				while ((ret = readdir(dir)))
					if (!ft_strcmp(ret->d_name, str))
					{
						closedir(dir);
						return (1);
					}
				closedir(dir);
			}
			paths++;
		}
	}
	return (0);
}

void			manage_initialize(t_lst *list, char **cmd, int len)
{
	char **paths_tmp;
	char *cmd_path;

	cmd_path = NULL;
	paths_tmp = parse_path(list);
	cmd_path = get_cmd_path(cmd[2], paths_tmp);
	if (len == 2)
		list = NULL;
	else if (len > 2)
	{
		if (cmd_is_in_path(cmd[2], paths_tmp))
			do_fork(list, cmd + 2, cmd_path);
		else
		{
			ft_putstr_fd("env: ", 2);
			ft_putstr_fd(cmd[3], 2);
			ft_putendl_fd(": No such file or directory", 2);
		}
	}
}

void			manage_env(t_lst *list, char **cmd, int len)
{
	int i;
	int j;
	char *cmd_path;
	char **paths;

	i = 1; // if 0 utilise env du systeme
	j = 0;
	cmd_path = NULL;
	paths = NULL;
	if (len >= 2)
	{
		while (cmd[i])
		{
//			do_print_env(list);//test
			paths = parse_path(list);
			if (cmd_is_in_path(cmd[i], paths))
			{
				printf("BBB\n");
				cmd_path = get_cmd_path(cmd[i], paths);
				do_fork(list, cmd + i, cmd_path);
				break ;
			}
//			while (cmd[i][j])
		//		if (cmd[i][j] == '=')
		//		{	
			else
			{
					printf("AAA\n");
					do_setenv(list, cmd, 2);
					break ;
			}
//			j++;
			i++;
		}
	}
}

void			do_env(t_lst *list, char **cmd)
{
	int		len;
	int		i;
	t_lst	*list_tmp;

	i = 0;
	len = ft_tablen(cmd);
	list_tmp = do_list_cpy(list);
	if (len == 1)
		do_print_env(list_tmp);
	if (len >= 2)
	{
		if (!ft_strcmp(cmd[1], "-u"))
			manage_unsetenv(list_tmp, cmd, len);
		else if (!ft_strcmp(cmd[1], "-i"))
			manage_initialize(list_tmp, cmd, len);
		else if (cmd[1])
			manage_env(list_tmp, cmd, len);
//		else
//			error illegal option
	}
}
