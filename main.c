#include "ft_ls.h"

int main (int ac, char **av)
{
	struct stat sb;

    for (int av_pos = 1; av_pos < ac; av_pos++)
    {
		if (av[av_pos][0] == '-')
		{
			printf("flags: %s\n", av[av_pos]);
		}
		else
		{
			if (stat(av[av_pos], &sb) == 0)
			{
				printf("path: %s\n", av[av_pos]);
				printf("%d", sb.st_mode);
			}
			else
			{
				cannot_access(av[0], av[av_pos]);
			}
		}
    }
}