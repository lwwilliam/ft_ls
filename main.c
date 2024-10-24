#include "ft_ls.h"

char *path_join(char *path, char *dir)
{
	char *new_path;
	char *slash_path;

	if (path[ft_strlen(path) - 1] != '/')
		slash_path = ft_strjoin(path, "/");
	else
		slash_path = ft_strdup(path);

	new_path = ft_strjoin(slash_path, dir);
	free(slash_path);
	return(new_path);
}

void sub_dir(char *path, char **dir_paths, struct s_cmd *initial_cmd)
{
	struct stat sb;
	for (int i = 0; dir_paths[i] != NULL; i++)
	{
		char *new_path = path_join(path, dir_paths[i]);
		if (stat(new_path, &sb) == 0)
		{
			if ((sb.st_mode & S_IFMT) == S_IFDIR && ft_strncmp(dir_paths[i], "..", 2) != 0 && ft_strncmp(dir_paths[i], ".\0", 2) != 0)
			{
				write(1, new_path, ft_strlen(new_path));
				write(1, ":\n", 2);
				read_dir(new_path, initial_cmd);
			}
			free(new_path);
		}
	}
}

void print_file(char *path, char *file, int whole_len, int max_len)
{
	char *new_path = path_join(path, file);
	int term_width = TERM_WIDTH
	struct stat sb;
	if (stat(new_path, &sb) == 0)
	{
		if ((sb.st_mode & S_IFMT) == S_IFDIR)
		{
			blue();
		} 
		else if (sb.st_mode & S_IXUSR || sb.st_mode & S_IXGRP || sb.st_mode & S_IXOTH)
		{
			green();
		}
		free(new_path);
	}
	write(1, file, ft_strlen(file));
	reset();
	if (whole_len > term_width)
	{
		for (int i = 0; i < (max_len - (int)ft_strlen(file)); i++)
			write(1, " ", 1);
	}
}

void row_col(char **files, int count, int max_len, char *path, int whole_len)
{
	int term_width = TERM_WIDTH
	int cols = term_width / (max_len + 2);
	int rows = (count + cols - 1) / cols;
	if (whole_len < term_width)
	{
		cols = cols * rows;
		rows = 1;
	}
	for (int i = 0; i < rows; ++i)
	{
		for (int j = 0; j < cols; ++j)
		{
			int index = i + j * rows;
			if (index < count)
			{
				print_file(path, files[index], whole_len, max_len);
				if (j < cols - 1)
					write(1, "  ", 2);
			}
		}
		write(1, "\n", 1);
	}
}

int read_dir(char *path, struct s_cmd *initial_cmd)
{
    DIR *dir;
    struct dirent *dp;
    char * file_name;
	char **dir_paths;
	int dir_paths_count;

    dir = opendir(path);
	dir_paths_count = 0; 
    while ((dp = readdir(dir)) != NULL)
	{
		if (dp->d_name[0] != '.' || (dp->d_name[0] == '.' && initial_cmd->a_flag == 1))
		{
			dir_paths_count++;
		}
    }
    closedir(dir);
    dir = opendir(path);
	dir_paths = malloc((dir_paths_count + 1) * sizeof(char *));
	dir_paths_count = 0;
	while ((dp = readdir(dir)) != NULL)
	{
		if (dp->d_name[0] != '.' || (dp->d_name[0] == '.' && initial_cmd->a_flag == 1))
        {
			file_name = dp->d_name;
			dir_paths[dir_paths_count] = ft_strdup(file_name);
			dir_paths_count++;
        }
    }
	bubble_sort(dir_paths, dir_paths_count);
	dir_paths[dir_paths_count] = NULL;
	int max_len;
	int whole_len;
	max_len = 0;
	whole_len = 0;
	for (int i = 0; dir_paths[i] != NULL; i++)
	{
		whole_len += ((int)ft_strlen(dir_paths[i]) + 2);
		int len = ft_strlen(dir_paths[i]);
		if (len > max_len)
			max_len = len;
	}

	row_col(dir_paths, dir_paths_count, max_len, path, whole_len);
	write(1, "\n", 1);
	if(initial_cmd->R_flag == 1)
		sub_dir(path, dir_paths, initial_cmd);
    closedir(dir);
	free2darr(dir_paths);
    return (0);
}

int main (int ac, char **av)
{
	struct s_cmd initial_cmd;
	ft_memset(&initial_cmd, 0, sizeof(struct s_cmd));

	init_parse(ac, av, &initial_cmd);

	for (int i = 0; initial_cmd.paths[i] != NULL; i++)
	{
		if (initial_cmd.path_len > 1 || initial_cmd.R_flag == 1)
		{
			write(1, initial_cmd.paths[i], ft_strlen(initial_cmd.paths[i]));
			write(1, ":\n", 2);
		}
		read_dir(initial_cmd.paths[i], &initial_cmd);
	}

	// printf("---------------------------------------------\n");
	// printf("l: %d\n", initial_cmd.l_flag);
	// printf("R: %d\n", initial_cmd.R_flag);
	// printf("a: %d\n", initial_cmd.a_flag);
	// printf("r: %d\n", initial_cmd.r_flag);
	// printf("t: %d\n", initial_cmd.t_flag);

	// for (int i = 0; initial_cmd.paths[i] != NULL; i++)
	// {
	// 	printf("path: %s\n", initial_cmd.paths[i]);
	// }

	free2darr(initial_cmd.paths);
	return 0;
}