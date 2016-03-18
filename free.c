/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fviolin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/17 16:05:53 by fviolin           #+#    #+#             */
/*   Updated: 2016/03/18 10:36:56 by fviolin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_ptrs(char **env_cpy, char **cmd, char **path_cpy)
{
	ft_print_tab(env_cpy); // test
	if (env_cpy && *env_cpy)
		ft_strdel(env_cpy);
	ft_print_tab(path_cpy); // test
	if (path_cpy && *path_cpy)
		ft_strdel(path_cpy);
	ft_print_tab(cmd); // test
	if (cmd && *cmd)
		ft_strdel(cmd);
}

void	free_fork(char **cmd_tmp, char **path, char *cmd_path, char *path_str)
{
	free_tab(cmd_tmp);
	free_tab(path);
	ft_strdel(&cmd_path);
	ft_strdel(&path_str);
}

void	free_tab(char **tab)
{
	int i;
	int len;

	if (tab)
	{
		if (*tab)
		{
			i = 0;
			len = ft_tablen(tab);
			while (i < len)
			{
				ft_strdel(&tab[i]);
				i++;
			}
		}
		free(tab);
		tab = NULL;
	}
}
