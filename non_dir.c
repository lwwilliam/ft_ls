#include "ft_ls.h"

void print_non_dir(struct s_cmd *initial_cmd)
{
	bubble_sort(initial_cmd->non_dir, initial_cmd->non_dir_len);
	if (initial_cmd->t_flag == 1)
		last_modified_sort(initial_cmd->non_dir, initial_cmd->non_dir_len, "#");
	if (initial_cmd->r_flag == 1)
		reverse_sort(initial_cmd->non_dir, initial_cmd->non_dir_len);

	if (initial_cmd->l_flag == 1)
		list_dir(".", initial_cmd->non_dir, initial_cmd->non_dir_len, 1);
	else
	{
		for (int i = 0; initial_cmd->non_dir[i]; i++)
		{
			write(1, initial_cmd->non_dir[i], ft_strlen(initial_cmd->non_dir[i]));
			write(1, "  ", 2);
		}
	}
	write(1, "\n", 1);
	if (initial_cmd->l_flag == 0 && initial_cmd->path_len > 0)
		write(1, "\n", 1);
}