#include "ft_ls.h"

int main (int ac, char **av)
{
	struct s_cmd initial_cmd;
	ft_memset(&initial_cmd, 0, sizeof(struct s_cmd));

	init_parse(ac, av, &initial_cmd);


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