/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwilliam <lwilliam@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 09:38:26 by lwilliam          #+#    #+#             */
/*   Updated: 2025/01/13 15:13:15 by lwilliam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H
# define FT_LS_H

# include <stdio.h>
# include <unistd.h>
# include <string.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <dirent.h>
# include <sys/sysmacros.h>
# include <sys/ioctl.h>
# include <pwd.h>
# include <grp.h>
# include <time.h>
# include "libft/libft.h"

# define TERM_WIDTH 150
// struct to store the initial arguments for ls
// if flag is 1 (it exist)
// path to store the path in the arguments
typedef struct s_cmd
{
	int		l_flag;
	int		r_flag;
	int		a_flag;
	int		rev_flag;
	int		t_flag;
	char	**paths;
	int		path_len;
	char	**non_dir;
	int		non_dir_len;
}	t_cmd;

// parser.c
void	init_parse(int ac, char **av, struct s_cmd *initial_cmd);
void	bubble_sort(char **paths, int count);
void	free2darr(char **arr);

// sub_dir.c
void	sub_dir(char *path, char **dir_paths, struct s_cmd *initial_cmd);
char	*path_join(char *path, char *dir);

//sort.c
void	bubble_sort(char **paths, int count);
void	reverse_sort(char **paths, int count);
void	last_modified_sort(char **paths, int count, char *parent_dir);

// list_print.c
void	list_dir_len(struct stat *sb, int *n_link_len, int *o_name_len, \
						int *o_group_len, int *size_len);
void	print_perms(struct stat *sb);

// error.c
void	cannot_access(char *cmd, char *path);
void	invalid_option(char *cmd, char invalid_flag);
void	print_help(char *cmd);
void	permission_denied(char *cmd, char *path);

//non_dir.c
void	print_non_dir(struct s_cmd *initial_cmd);

// main.c
void	list_dir(char *path, char **files, int count, int non_dir);
int		read_dir(char *path, struct s_cmd *initial_cmd);
void	row_col(char **files, int count, int max_len, char *path, \
					int whole_len);
void	print_padding(char *str, int p_size);
void	print_link_name_size(struct stat *sb, int n_link_len, int o_name_len, \
								int o_group_len, int size_len);
void	print_time(struct stat *sb);

//colors
void	yellow(void);
void	blue(void);
void	green(void);
void	cyan(void);
void	reset(void);

#endif