/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fviolin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/13 14:57:53 by fviolin           #+#    #+#             */
/*   Updated: 2016/03/18 13:17:35 by fviolin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void		color(char *color, char *target)
{
	ft_putchar_fd('\033', 2);
	ft_putstr_fd(color, 2);
	ft_putstr_fd(target, 2);
}

static void		prompt_user(char **env)
{
	char *user;

	user = get_env_content(env, "USER");
	if (user)
	{
		ft_putstr("# ");
		color(YELLOW, user);
		color(RESET, "");
		ft_putstr(" in ");
	}
	ft_strdel(&user);
}

void			prompt(char **env)
{
	char	*home;
	char	buf[100];

	getcwd(buf, 100);
	home = get_env_content(env, "HOME");
	prompt_user(env);
	if (home && ft_strstr(buf, home))
	{
		color(GREEN, "");
		ft_putchar('~');
		ft_putstr(ft_strstr(buf, home) + ft_strlen(home));
		color(RESET, "");
	}
	else
		ft_putstr(buf);
	color(RED, " \n$> ");
	color(RESET, "");
	ft_strdel(&home);
}
