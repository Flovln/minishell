/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fviolin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/29 10:34:00 by fviolin           #+#    #+#             */
/*   Updated: 2016/03/12 18:17:47 by fviolin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
* * Function for getting content in env variables
*/

char	*get_env_content(char **env, char *str)
{
	int		i;
	int		start;
	char	*tmp;
	char	*content;

	if (env && *env)
	{
		i = 0;
		while (env[i])
		{
			if (!ft_strncmp(env[i], str, ft_strlen(str)))
			{
				start = ft_strlen(str) + 1;
				tmp = ft_strsub(env[i], start, ft_strlen(env[i] - start));
				content = ft_strdup(tmp);
				ft_strdel(&tmp);
				return (content);
			}
			i++;
		}
	}
	return (NULL);
}

/*
* * Pimped Prompt oh_my_zsh style
*/

void	prompt(char **env)
{
	char *home;
	char *user;
	char cwd[100];

	getwd(cwd);
	printf("env in prompt = |%s|\n", *env); // TEST
	printf("cwd in prompt = |%s|\n", cwd); // TEST
	home = get_env_content(env, "HOME");
	printf("home in prompt = |%s|\n", home); // TEST
	user = get_env_content(env, "USER");
	printf("user in prompt = |%s|\n", user); // TEST
	if (user)
		ft_putstr(user);
	else
		ft_putstr("no user");
	ft_putchar(' ');
	if (home && ft_strstr(cwd, home))
	{
		ft_putchar('~');
		ft_putstr(ft_strstr(cwd, home) + ft_strlen(home));
	}
	else
		ft_putstr(cwd);
	write(1, " \n$> ", 5);
	ft_strdel(&home);
	ft_strdel(&user);
}

/*
* * Function Duplicating env
*/

char	**tab_dup(char **tab)
{
	int		i;
	int		len;
	char	**tmp;

	if (tab)
	{
		i = 0;
		len = ft_tablen(tab);
		if (!(tmp = (char **)malloc(sizeof(char *) * (len + 1))))
			return (NULL);
		while (i < len)
		{
			tmp[i] = ft_strdup(tab[i]);
			i++;
		}
		tmp[i] = NULL;
		return (tmp);
	}
	return (NULL);
}

int		main(int ac, char **av, char **env)
{
	char	**cpy_env;
	char	*line;
//	pid_t 	pid;

//	pid = fork();
	cpy_env = NULL;
	av = NULL;
	cpy_env = tab_dup(env);
	if (ac == 1)
	{
		while (1)
		{
			prompt(cpy_env);
			if (get_next_line(0, &line) == 1)
			{
//				ft_putendl("Test Prompt");
//				printf("line in Gnl -> |%s|\n", line);
			}
			if (ft_strcmp(line, "exit") == 0)
			{
//				ft_putendl("Test Exit");
				break ;
			}
		}
	}
	return (0);
}
