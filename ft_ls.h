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

# define TERM_WIDTH 120;
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

// sub_dir.c
void sub_dir(char *path, char **dir_paths, struct s_cmd *initial_cmd);
char *path_join(char *path, char *dir);

//sort.c
void bubble_sort(char **paths, int count);
void reverse_sort(char **paths, int count);
void last_modified_sort(char **paths, int count, char *parent_dir);

// main.c
int read_dir(char *path, struct s_cmd *initial_cmd);
void row_col(char **files, int count, int max_len, char *path, int whole_len);

//colors
void red ();
void yellow();
void blue();
void green();
void reset ();

#endif