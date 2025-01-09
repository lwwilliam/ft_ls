/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   non_dir.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwilliam <lwilliam@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 10:13:23 by lwilliam          #+#    #+#             */
/*   Updated: 2025/01/09 10:15:09 by lwilliam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	print_non_dir(struct s_cmd *initial_cmd)
{
	int	i;

	bubble_sort(initial_cmd->non_dir, initial_cmd->non_dir_len);
	if (initial_cmd->t_flag == 1)
		last_modified_sort(initial_cmd->non_dir, initial_cmd->non_dir_len, "#");
	if (initial_cmd->rev_flag == 1)
		reverse_sort(initial_cmd->non_dir, initial_cmd->non_dir_len);
	if (initial_cmd->l_flag == 1)
		list_dir(".", initial_cmd->non_dir, initial_cmd->non_dir_len, 1);
	else
	{
		i = 0;
		while (initial_cmd->non_dir[i])
		{
			write(1, initial_cmd->non_dir[i], \
				ft_strlen(initial_cmd->non_dir[i]));
			write(1, "  ", 2);
			i++;
		}
	}
	write(1, "\n", 1);
	if (initial_cmd->l_flag == 0 && initial_cmd->path_len > 0)
		write(1, "\n", 1);
}
