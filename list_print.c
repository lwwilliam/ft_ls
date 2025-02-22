/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_print.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwilliam <lwilliam@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 09:57:59 by lwilliam          #+#    #+#             */
/*   Updated: 2025/01/09 10:12:48 by lwilliam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	list_dir_len(struct stat *sb, int *n_link_len, int *o_name_len, int *o_group_len, int *size_len)
{
	struct passwd	*pw;
	struct group	*gr;
	char			*n_link;
	char			*size;

	pw = getpwuid(sb->st_uid);
	gr = getgrgid(sb->st_gid);
	n_link = ft_itoa(sb->st_nlink);
	if (*n_link_len < (int)ft_strlen(n_link))
		*n_link_len = ft_strlen(n_link);
	free(n_link);
	if (*o_name_len < (int)ft_strlen(gr->gr_name))
		*o_name_len = ft_strlen(gr->gr_name);
	if (*o_group_len < (int)ft_strlen(pw->pw_name))
		*o_group_len = ft_strlen(pw->pw_name);
	size = ft_itoa(sb->st_size);
	if (*size_len < (int)ft_strlen(size))
		*size_len = ft_strlen(size);
	free(size);
}

void	print_perms(struct stat *sb)
{
	write(1, (S_ISDIR(sb->st_mode)) ? "d" : "-", 1);
	write(1, (sb->st_mode & S_IRUSR) ? "r" : "-", 1);
	write(1, (sb->st_mode & S_IWUSR) ? "w" : "-", 1);
	if (sb->st_mode & S_ISUID)
		write(1, (sb->st_mode & S_IXUSR) ? "s" : "S", 1);
	else
		write(1, (sb->st_mode & S_IXUSR) ? "x" : "-", 1);
	write(1, (sb->st_mode & S_IRGRP) ? "r" : "-", 1);
	write(1, (sb->st_mode & S_IWGRP) ? "w" : "-", 1);
	if (sb->st_mode & S_ISGID)
		write(1, (sb->st_mode & S_IXGRP) ? "s" : "S", 1);
	else
		write(1, (sb->st_mode & S_IXGRP) ? "x" : "-", 1);
	write(1, (sb->st_mode & S_IROTH) ? "r" : "-", 1);
	write(1, (sb->st_mode & S_IWOTH) ? "w" : "-", 1);
	if (sb->st_mode & S_ISVTX)
		write(1, (sb->st_mode & S_IXOTH) ? "t" : "T", 1);
	else
		write(1, (sb->st_mode & S_IXOTH) ? "x" : "-", 1);

	write(1, " ", 1);
}

void	print_padding(char *str, int p_size)
{
	int	i;

	if ((int)ft_strlen(str) < p_size)
	{
		i = p_size - ft_strlen(str);
		while (i > 0)
		{
			write(1, " ", 1);
			i--;
		}
	}
	write(1, str, ft_strlen(str));
	write(1, " ", 1);
}

void	print_link_name_size(struct stat *sb, int n_link_len, int o_name_len, int o_group_len, int size_len)
{
	struct passwd	*pw;
	struct group	*gr;
	char			*n_link;
	char			*size;

	pw = getpwuid(sb->st_uid);
	gr = getgrgid(sb->st_gid);
	n_link = ft_itoa(sb->st_nlink);
	print_padding(n_link, n_link_len);
	free(n_link);
	print_padding(gr->gr_name, o_name_len);
	print_padding(pw->pw_name, o_group_len);
	size = ft_itoa(sb->st_size);
	print_padding(size, size_len);
	free(size);
}

void	print_time(struct stat *sb)
{
	char	*time_str;
	char	**date_arr;

	time_str = ctime(&sb->st_mtime);
	date_arr = ft_split(time_str, ' ');
	write(1, date_arr[1], ft_strlen(date_arr[1]));
	write(1, " ", 1);
	if (ft_strlen(date_arr[2]) < 2)
		write(1, " ", 1);
	write(1, date_arr[2], ft_strlen(date_arr[2]));
	write(1, " ", 1);
	write(1, date_arr[3], ft_strlen(date_arr[3]));
	write(1, " ", 1);
	free2darr(date_arr);
}
