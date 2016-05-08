/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   21sh.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fviolin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/18 11:24:18 by fviolin           #+#    #+#             */
/*   Updated: 2016/05/02 13:19:15 by fviolin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TWTWOSH_H
# define TWTWOSH_H

# include "../../libft/libft.h"
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <dirent.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <sys/dir.h>
# include <sys/stat.h>
# include <dirent.h>

# define RED "[31m"
# define GREEN "[32m"
# define YELLOW "[33m"
# define RESET "[39m"

typedef struct		s_lst
{
	char			*name;
	char			*content;
	struct s_lst	*next;
}					t_lst;

t_lst				*create_node(char **env);
void				list_push_node(t_lst **head, t_lst *new_node);
void				list_remove_node(t_lst **node, char *varname);
int					get_list_len(t_lst *list);
char				**list_in_tab(t_lst *list);
char				*get_var_content(char *str);
char				*get_var_name(char *str);
void				do_prompt(t_lst *list);
char				**parse_path(t_lst *list);
void				parse_cmd(t_lst *list, char **cmd, char *str);
void				manage_cmd(t_lst *list, char **cmd, char **paths);
void				do_fork(t_lst *list, char **cmd, char *cmd_path);
char				*get_cmd_path(char *cmd, char **paths);
void				permissions_error_handl(t_lst *list, char **cmd);
int					cmd_in_var(t_lst *list, char *cmd, char *var);
int					check_is_builtin(char *cmd);
void				do_builtins(t_lst *list, char **cmd); //, char **paths);
void				do_setenv(t_lst *list, char **cmd, int flag);
void				do_unsetenv(t_lst *list, char **cmd);
int					check_is_alpha(char *str);
void				do_env(t_lst *list, char **cmd); //, char **paths);
void				do_print_env(t_lst *list);
void				manage_unsetenv(t_lst *list, char **cmd, int len);
int					cmd_is_in_path(char *str, char **paths);
void				do_cd(t_lst *list, char **cmd);
void				ft_error(char *err, int flag);
char				*get_content(t_lst *list, char *str);
int					check_var_exists(t_lst *list, char *var_name);
void				update_var_content(t_lst *list, char *var_name, char *str);

#endif
