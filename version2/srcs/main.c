/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fviolin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/18 11:28:37 by fviolin           #+#    #+#             */
/*   Updated: 2016/05/01 18:01:53 by fviolin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/twtwosh.h"

void	get_stdin(t_lst *list)
{
	char	*line;
	char	**cmd;

	line = NULL;
	cmd = NULL;
	while (1)
	{
		do_prompt(list);
		if (get_next_line(0, &line) != -1)
		{
			cmd = ft_strsplit(line, ';');
//			ft_strdel(&line);
			while (*cmd)
			{
				parse_cmd(list, cmd, *cmd);	
				cmd++;
			}
			ft_putchar('\n');
		}
	}
}

int		main(int ac, char **av, char **env)
{
	t_lst	*list;
	char	**env_cpy;

	av = NULL;
	list = NULL;
	env_cpy = ft_tabdup(env);
	while (*env_cpy)
	{
		list_push_node(&list, create_node(env_cpy));
		env_cpy++;
	}
	signal(SIGINT, SIG_IGN);
	if (ac == 1)
		get_stdin(list);
	else
		return (1);
	ft_strdel(env_cpy);
	return (0);
}
