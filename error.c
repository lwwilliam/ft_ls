/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwilliam <lwilliam@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 09:55:23 by lwilliam          #+#    #+#             */
/*   Updated: 2025/01/09 09:56:00 by lwilliam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	cannot_access(char *cmd, char *path)
{
	write(1, cmd, ft_strlen(cmd));
	write(1, ": cannot access '", 17);
	write(1, path, strlen(path));
	write(1, "': No such file or directory\n", 30);
}

void	invalid_option(char *cmd, char invalid_flag)
{
	write(1, cmd, ft_strlen(cmd));
	write(1, ": invalid option -- '", 21);
	write(1, &invalid_flag, 1);
	write(1, "'\n", 2);
	write(1, "Try '", 5);
	write(1, cmd, ft_strlen(cmd));
	write (1, " --help' for more information.\n", 32);
	exit(1);
}

void	print_help(char *cmd)
{
	write(1, "Usage: ", 7);
	write(1, cmd, ft_strlen(cmd));
	write(1, "[OPTION]... [FILE]...\n", 22);
	write(1, "OPTIONS: -l    -R    -a    -r    -t\n", 37);
	exit(1);
}
