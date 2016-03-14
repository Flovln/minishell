/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fviolin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/29 10:21:19 by fviolin           #+#    #+#             */
/*   Updated: 2016/03/14 12:39:02 by fviolin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/dir.h>

#include "libft/libft.h"
/*
typedef struct		s_exe
{
	char			*line;
	char			**cmd_path;
	char			**path_cpy;
}					t_exe;
*/
void	prompt(char **env);
char	*get_env_content(char **env, char *str);
char	**tab_dup(char **tab);
void	exe_cmd(char **env, char **cmd, char **path_cpy);
char	*get_cmd_path(char *cmd, char **path);

#endif
