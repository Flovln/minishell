/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fviolin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/13 14:57:53 by fviolin           #+#    #+#             */
/*   Updated: 2016/03/19 17:07:06 by fviolin          ###   ########.fr       */
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
	else
		ft_putstr("no USER var ");
	ft_strdel(&user);
}

static void		prompt_path(char *home, char *buf)
{
	if (home && ft_strstr(buf, home))
	{
		color(GREEN, "");
		ft_putchar('~');
		ft_putstr(ft_strstr(buf, home) + ft_strlen(home));
		color(RESET, "");
	}
	else if (buf[0])
		ft_putstr(buf);
	color(RED, " \n$> ");
	color(RESET, "");
}

static char		**update_pwd(char **env, char *str, char *wd)
{
	int		i;
	char	*tmp;

	if (env && *env)
	{
		i = -1;
		while (env[++i])
			if (!ft_strncmp(env[i], str, ft_strlen(str)))
			{
				tmp = ft_strdup(env[i]);
				tmp = ft_strjoin(str, wd);
				env[i] = tmp;
				return (env);
			}
		return (env);
	}
	return (NULL);
}

void			prompt(char **env, int count)
{
	char	*home;
	char	buf[100];
	char	*pwd_str;

	if (count > 0)
		pwd_str = get_env_content(env, "PWD");
	else
		pwd_str = ft_strnew(200);
	ft_bzero(buf, 100);
	getcwd(buf, 100);
	env = update_pwd(env, "PWD=", buf);
	home = get_env_content(env, "HOME");
	prompt_user(env);
	prompt_path(home, buf);
	if (count > 0)
		env = update_pwd(env, "OLDPWD=", pwd_str);
	ft_strdel(&home);
}
