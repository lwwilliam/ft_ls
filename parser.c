#include "ft_ls.h"

void cannot_access(char *cmd, char *path)
{
	write(1, cmd, ft_strlen(cmd));
	write(1, ": cannot access '", 17);
	write(1, path, strlen(path));
	write(1, "': No such file or directory\n", 30);
}

void check_flag(struct s_cmd *initial_cmd, char flag)
{
	switch (flag)
	{
		case 'l':
			initial_cmd->l_flag = 1;
			break;
		case 'R':
			initial_cmd->R_flag = 1;
			break;
		case 'a':
			initial_cmd->a_flag = 1;
			break;
		case 'r':
			initial_cmd->r_flag = 1;
			break;
		case 't':
			initial_cmd->t_flag = 1;
			break;
	}
}

void check_path(char *path, char *prog_name, int *path_count)
{
	struct stat sb;
	if (stat(path, &sb) == 0)
	{
		(*path_count)++;
	}
	else
	{
		cannot_access(prog_name, path);
	}
}

void swap(char **a, char **b) {
    char *temp = *a;
    *a = *b;
    *b = temp;
}

// Bubble sort function
void bubble_sort(char **paths, int count) {
    for (int i = 0; i < count - 1; i++) {
        for (int j = 0; j < count - i - 1; j++) {
            if (ft_strncmp(paths[j], paths[j + 1], 256) > 0) {
                swap(&paths[j], &paths[j + 1]);
            }
        }
    }
}

void init_parse(int ac, char **av, struct s_cmd *initial_cmd)
{
	int path_count;
	int err;

	err = 0; /* if err = 1 dont put "." that means the argument is something like this(ls -l dasdasd) \
	this is to handle command like (ls -l) so that "." will add into the path if err remains 0 */
	path_count = 0;
	for (int av_pos = 1; av_pos < ac; av_pos++)
    {
		if (av[av_pos][0] == '-')
		{
			for (int i = 1; av[av_pos][i]; i++)
				check_flag(initial_cmd, av[av_pos][i]);
		}
		else
		{
			check_path(av[av_pos], av[0], &path_count);
			err = 1;
		}
    }
	if (err == 0 && path_count == 0)
		initial_cmd->paths = malloc((2) * sizeof(char *));
	else
		initial_cmd->paths = malloc((path_count + 1) * sizeof(char *));
	path_count = 0;
	for (int av_pos = 1; av_pos < ac; av_pos++)
    {
		if (av[av_pos][0] != '-')
		{
			struct stat sb;
			if (stat(av[av_pos], &sb) == 0)
			{
				initial_cmd->paths[path_count] = ft_strdup(av[av_pos]);
				path_count++;
			}
		}
    }
	bubble_sort(initial_cmd->paths, path_count);
	if (err == 0 && path_count == 0)
	{
		initial_cmd->paths[path_count] = ft_strdup(".");
		path_count++;
	}
	initial_cmd->paths[path_count] = NULL;
	initial_cmd->path_len = path_count;
}