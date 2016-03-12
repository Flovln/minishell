/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fviolin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/29 10:34:00 by fviolin           #+#    #+#             */
/*   Updated: 2016/03/12 16:40:17 by fviolin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	prompt()
{
	write(1, "$> ", 3);
}



int		main(int ac, char **av, char **env)
{
	char	**cpy_env;
	char	*line;
//	pid_t 	pid;

//	pid = fork();
	cpy_env = NULL;
	av = NULL;
	env = NULL;
	if (ac == 1)
	{
		while (1)
		{
			prompt();
			if (get_next_line(0, &line) == 1)
			{
				ft_putendl("Test Prompt");
				printf("line in Gnl -> |%s|\n", line);
			}
			if (ft_strcmp(line, "exit") == 0)
			{
				ft_putendl("Test Exit");
				break ;
			}
		}
	}
	return (0);
}
