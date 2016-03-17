/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fviolin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/29 10:21:19 by fviolin           #+#    #+#             */
/*   Updated: 2016/03/17 15:43:11 by fviolin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/dir.h>
#include <sys/stat.h>
#include <dirent.h>

#include "libft/libft.h"

#define DEBUG printf("%d: %s\n", __LINE__, __func__); /* ---DEBUG--- */

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
void	print_env(char **env);
void	manage_exe_cmd(char **env, char **cmd, char **path_cpy);
char	*get_cmd_path(char *cmd, char **path);
void	exe_fork(char **env, char **cmd, char *cmd_path);

/*
 * * Builtin Functions
 */

int		is_include(char **env, char *cmd);
int		is_builtin(char *cmd);
char	**do_builtin(char **cmd, char **env);
char	**do_cd(char **cmd, char **env);

char	**add_str(char **env, char **new_env, char **cmd, int len);
int		is_include(char **env, char *cmd);
char	**do_setenv(char **env, char **cmd);
char	**do_unsetenv(char **env, char **cmd);
char	**do_env(char **env, char **cmd);
int		ft_multi_strcmp(char *s, char *s1, char *s2);

/*
 * * Tools Functions
 */
void	ft_print_tab(char **tab); //test

int		ft_occ_nb(char *s, char c);
char	*ft_strcdup(char *s, char c);

char	**setenv_redirection(char **env, char **cmd);
char	**resize_cmd(char **cmd, char **cmd_tmp, int flag);
void	fork_redirection(char **env, char **cmd, int flag);
char	**ignore_env(char **env, int len);
char	**tab_dup(char **tab);
void	free_tab(char **tab);
void	free_ptr(/*char **env_cpy, */char **cmd, char **path_cpy);
void	free_fork(char **cmd_tmp, char **path, char *cmd_path, char *path_str);

#endif
