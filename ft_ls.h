#ifndef FT_LS_H
# define FT_LS_H

#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <dirent.h>
#include <sys/sysmacros.h>
#include <sys/ioctl.h>
#include "libft/libft.h"

# define TERM_WIDTH 150;
// struct to store the initial arguments for ls
// if flag is 1 (it exist)
// path to store the path in the arguments
typedef struct s_cmd
{
	int l_flag;
	int R_flag;
	int a_flag;
	int r_flag;
	int t_flag;
	char **paths;
	int path_len;
} t_cmd;

// parser.c
void cannot_access(char *cmd, char *path);
void init_parse(int ac, char **av, struct s_cmd *initial_cmd);
void bubble_sort(char **paths, int count);
void free2darr(char **arr);
int read_dir(char *path, struct s_cmd *initial_cmd);

//colors
void red ();
void yellow();
void blue();
void green();
void reset ();

#endif