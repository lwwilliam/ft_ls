#include "ft_ls.h"

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
	if (initial_cmd->t_flag == 1)
		last_modified_sort(dir_paths, dir_paths_count, path);
	if (initial_cmd->r_flag == 1)
		reverse_sort(dir_paths, dir_paths_count);
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