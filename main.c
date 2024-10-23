#include "ft_ls.h"

int read_dir(char *path)
{
    DIR *dir;
    struct dirent *dp;
    char * file_name;
    dir = opendir(path);
    while ((dp = readdir(dir)) != NULL) {
        if (dp->d_name[0] == '.')
        {

        } 
		else
		{
            file_name = dp->d_name;
			// write(1, file_name, ft_strlen(file_name));
			printf("file_name: %s   %u \n", file_name, dp->d_type);
			// write(1, dp->d_type, ft_strlen(dp->d_type));
			// write(1, " ", 1);
        }
    }
	write(1, "\n", 1);
    closedir(dir);
    return (0);
}

int main (int ac, char **av)
{
	struct s_cmd initial_cmd;
	ft_memset(&initial_cmd, 0, sizeof(struct s_cmd));

	init_parse(ac, av, &initial_cmd);

	for (int i = 0; initial_cmd.paths[i] != NULL; i++)
	{
		read_dir(initial_cmd.paths[i]);
	}


	printf("l: %d\n", initial_cmd.l_flag);
	printf("R: %d\n", initial_cmd.R_flag);
	printf("a: %d\n", initial_cmd.a_flag);
	printf("r: %d\n", initial_cmd.r_flag);
	printf("t: %d\n", initial_cmd.t_flag);

	for (int i = 0; initial_cmd.paths[i] != NULL; i++)
	{
		printf("str: %s\n", initial_cmd.paths[i]);
	}

	for (int i = 0; initial_cmd.paths[i] != NULL; i++) {
        free(initial_cmd.paths[i]);
    }
    free(initial_cmd.paths);
	return 0;
}