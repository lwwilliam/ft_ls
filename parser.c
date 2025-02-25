#include "ft_ls.h"

void check_flag(struct s_cmd *initial_cmd, char flag, char *prog_name)
{
	switch (flag)
	{
		case 'l':
			initial_cmd->l_flag = 1;
			break;
		case 'R':
			initial_cmd->r_flag = 1;
			break;
		case 'a':
			initial_cmd->a_flag = 1;
			break;
		case 'r':
			initial_cmd->rev_flag = 1;
			break;
		case 't':
			initial_cmd->t_flag = 1;
			break;
		default:
			invalid_option(prog_name, flag);
	}
}

void check_path(char *path, char *prog_name, int *path_count, int *file_count)
{
	struct stat sb;
	if (stat(path, &sb) == 0)
	{
		if (!S_ISDIR(sb.st_mode))
			(*file_count)++;
		else
			(*path_count)++;
	}
	else
	{
		cannot_access(prog_name, path);
	}
}

void init_parse(int ac, char **av, struct s_cmd *initial_cmd)
{
	int path_count;
	int file_count;
	int err;
	int i;

	err = 0; /* if err = 1 dont put "." that means the argument is something like this(ls -l dasdasd) \
	this is to handle command like (ls -l) so that "." will add into the path if err remains 0 */
	path_count = 0;
	file_count = 0;
	i = 0;
	for (int av_pos = 1; av_pos < ac; av_pos++)
    {
		if (av[av_pos][0] == '-')
		{
			if (!ft_strncmp(av[av_pos], "--help", 7))
				print_help(av[0]);
			for (int i = 1; av[av_pos][i]; i++)
				check_flag(initial_cmd, av[av_pos][i], av[0]);
		}
		else
		{
			check_path(av[av_pos], av[0], &path_count, &file_count);
			err = 1;
		}
    }
	if (err == 0 && path_count == 0 && file_count == 0)
	{
		initial_cmd->paths = malloc((2) * sizeof(char *));
		initial_cmd->non_dir = malloc((2) * sizeof(char *));
	}
	else
	{
		initial_cmd->paths = malloc((path_count + 1) * sizeof(char *));
		initial_cmd->non_dir = malloc((file_count + 1) * sizeof(char *));
	}

	path_count = 0;
	for (int av_pos = 1; av_pos < ac; av_pos++)
	{
		if (av[av_pos][0] != '-')
		{
			struct stat sb;
			if (stat(av[av_pos], &sb) == 0)
			{
				if (!S_ISDIR(sb.st_mode))
				{
					initial_cmd->non_dir[i] = ft_strdup(av[av_pos]);
					i++;
				}
				else
				{
					initial_cmd->paths[path_count] = ft_strdup(av[av_pos]);
					path_count++;
				}
			}
		}
	}
	bubble_sort(initial_cmd->paths, path_count);
	if (initial_cmd->t_flag == 1)
		last_modified_sort(initial_cmd->paths, path_count, "#");
	if (initial_cmd->rev_flag == 1)
		reverse_sort(initial_cmd->paths, path_count);
	if (err == 0 && path_count == 0)
	{
		initial_cmd->paths[path_count] = ft_strdup(".");
		path_count++;
	}
	initial_cmd->paths[path_count] = NULL;
	initial_cmd->non_dir[i] = NULL;
	initial_cmd->path_len = path_count;
	initial_cmd->non_dir_len = i;
}

void free2darr(char **arr)
{
	for (int i = 0; arr[i] != NULL; i++) {
		free(arr[i]);
	}
	free(arr);	
}
