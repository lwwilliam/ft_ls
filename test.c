#include "ft_ls.h"

void cannot_access(char *cmd, char *path)
{
	write(1, cmd, ft_strlen(cmd));
	write(1, ": cannot access '", 17);
	write(1, path, strlen(path));
	write(1, "': No such file or directory\n", 30);
}