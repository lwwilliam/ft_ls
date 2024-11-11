#include "ft_ls.h"

void list_dir_len(struct stat *sb, int *n_link_len, int *o_name_len, int *o_group_len, int *size_len)
{
	struct passwd *pw = getpwuid(sb->st_uid);
	struct group  *gr = getgrgid(sb->st_gid);
	char *n_link = ft_itoa(sb->st_nlink);
	if (*n_link_len < (int)ft_strlen(n_link))
		*n_link_len = ft_strlen(n_link);
	free(n_link);
	if (*o_name_len <  (int)ft_strlen(gr->gr_name))
		*o_name_len = ft_strlen(gr->gr_name);
	if (*o_group_len <  (int)ft_strlen(pw->pw_name))
		*o_group_len = ft_strlen(pw->pw_name);
	char *size = ft_itoa(sb->st_size);
	if (*size_len <  (int)ft_strlen(size))
		*size_len = ft_strlen(size);
	free(size);
}

void print_perms(struct stat *sb)
{
	write(1, (S_ISDIR(sb->st_mode)) ? "d" : "-", 1);
	write(1, (sb->st_mode & S_IRUSR) ? "r" : "-" , 1);
	write(1, (sb->st_mode & S_IWUSR) ? "w" : "-" , 1);
	write(1, (sb->st_mode & S_IXUSR) ? "x" : "-" , 1);
	write(1, (sb->st_mode & S_IRGRP) ? "r" : "-" , 1);
	write(1, (sb->st_mode & S_IWGRP) ? "w" : "-" , 1);
	write(1, (sb->st_mode & S_IXGRP) ? "x" : "-" , 1);
	write(1, (sb->st_mode & S_IROTH) ? "r" : "-" , 1);
	write(1, (sb->st_mode & S_IWOTH) ? "w" : "-" , 1);
	write(1, (sb->st_mode & S_IXOTH) ? "x" : (sb->st_mode & __S_ISVTX) ? "T" : "-" , 1);
	write(1, " ", 1);
}

void print_padding(char *str, int p_size)
{
	if ((int)ft_strlen(str) < p_size)
		for (int i = p_size - ft_strlen(str); i > 0; i--)
			write(1, " ", 1);
	write(1, str, ft_strlen(str));
	write(1, " ", 1);

}

void print_link_name_size(struct stat *sb, int n_link_len, int o_name_len, int o_group_len, int size_len)
{
	struct passwd *pw = getpwuid(sb->st_uid);
	struct group  *gr = getgrgid(sb->st_gid);

	char *n_link = ft_itoa(sb->st_nlink);
	print_padding(n_link, n_link_len);
	free(n_link);

	print_padding(gr->gr_name, o_name_len);
	print_padding(pw->pw_name, o_group_len);

	char *size = ft_itoa(sb->st_size);
	print_padding(size, size_len);
	free(size);
}

void print_time(struct stat *sb)
{
	char *time_str = ctime(&sb->st_mtime);
	char **date_arr = ft_split(time_str, ' ');
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