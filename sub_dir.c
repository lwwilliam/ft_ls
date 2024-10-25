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