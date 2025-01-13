#include "ft_ls.h"

void list_dir(char *path, char **files, int count, int non_dir)
{
	struct stat sb;
	int n_link_len = 0;
	int o_name_len = 0;
	int o_group_len = 0;
	int size_len = 0;
	long total_blocks = 0;
	for (int i = 0; i < count; i++)
	{
		char *new_path;
		if (non_dir == 0)
			new_path = path_join(path, files[i]);
		else
			new_path = ft_strdup(files[i]);
		if (lstat(new_path, &sb) == 0)
		{
			list_dir_len(&sb, &n_link_len, &o_name_len, &o_group_len, &size_len);
			total_blocks += sb.st_blocks;
			free(new_path);
		}
	}

	if (non_dir == 0)
	{
		char *block_char = ft_itoa(total_blocks / 2);
		write(1, "total ", 7);
		write(1, block_char, ft_strlen(block_char));
		write(1, "\n", 1);
		free(block_char);
	}
	for (int i = 0; i < count; i++)
	{
		char *new_path;
		if (non_dir == 0)
			new_path = path_join(path, files[i]);
		else
			new_path = ft_strdup(files[i]);
		if (lstat(new_path, &sb) == 0)
		{
			print_perms(&sb);
			print_link_name_size(&sb, n_link_len, o_name_len, o_group_len, size_len);
			print_time(&sb);
			if (S_ISDIR(sb.st_mode))
				blue();
			else if (S_ISLNK(sb.st_mode))
				cyan();
			else if (sb.st_mode & S_IXUSR || sb.st_mode & S_IXGRP || sb.st_mode & S_IXOTH)
				green();
			write(1, files[i], ft_strlen(files[i]));
			if (S_ISLNK(sb.st_mode))
			{
				char target[1024];
				ssize_t len = readlink(new_path, target, sizeof(target) - 1);
				if (len != -1)
				{
					target[len] = '\0';
					write(1, " -> ", 4);
					write(1, target, len);
				}
			}
			reset();
			free(new_path);
			if (non_dir == 0 || !ft_strncmp(path, ".", 2))
				write(1, "\n", 1);
		}
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
	if (!dir)
	{
		permission_denied("./ft_ls", path);
		return(1);
	}
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
	dir_paths[dir_paths_count] = NULL;
	bubble_sort(dir_paths, dir_paths_count);
	if (initial_cmd->t_flag == 1)
		last_modified_sort(dir_paths, dir_paths_count, path);
	if (initial_cmd->rev_flag == 1)
		reverse_sort(dir_paths, dir_paths_count);
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

	if (initial_cmd->l_flag == 1)
		list_dir(path, dir_paths, dir_paths_count, 0);
	else
		row_col(dir_paths, dir_paths_count, max_len, path, whole_len);
	if (initial_cmd->r_flag == 1)
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
	if (initial_cmd.non_dir_len > 0)
		print_non_dir(&initial_cmd);

	for (int i = 0; initial_cmd.paths[i] != NULL; i++)
	{
		DIR *dir = opendir(initial_cmd.paths[i]);
		if (dir)
		{
			if (initial_cmd.path_len > 1 || initial_cmd.r_flag == 1 || (initial_cmd.path_len == 1 && initial_cmd.non_dir_len > 0))
			{
				write(1, initial_cmd.paths[i], ft_strlen(initial_cmd.paths[i]));
				write(1, ":\n", 2);
			}
		}
		closedir(dir);
		read_dir(initial_cmd.paths[i], &initial_cmd);
		if (initial_cmd.paths[i + 1] != NULL)
			write(1, "\n", 1);
	}

	// printf("---------------------------------------------\n");
	// printf("l: %d\n", initial_cmd.l_flag);
	// printf("R: %d\n", initial_cmd.r_flag);
	// printf("a: %d\n", initial_cmd.a_flag);
	// printf("r: %d\n", initial_cmd.rev_flag);
	// printf("t: %d\n", initial_cmd.t_flag);

	// for (int i = 0; initial_cmd.paths[i] != NULL; i++)
	// {
	// 	printf("path: %s\n", initial_cmd.paths[i]);
	// }

	free2darr(initial_cmd.paths);
	free2darr(initial_cmd.non_dir);
	return 0;
}