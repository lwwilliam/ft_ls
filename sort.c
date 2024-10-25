#include "ft_ls.h"

void swap(char **a, char **b) {
    char *temp = *a;
    *a = *b;
    *b = temp;
}

void bubble_sort(char **paths, int count)
{
    for (int i = 0; i < count - 1; i++) {
        for (int j = 0; j < count - i - 1; j++) {
            if (ft_strncmp(paths[j], paths[j + 1], 256) > 0) {
                swap(&paths[j], &paths[j + 1]);
            }
        }
    }
}

void reverse_sort(char **paths, int count)
{
    for (int i = 0; i < count / 2; i++)
    {
        swap(&paths[i], &paths[count - i - 1]);
    }
}

void last_modified_sort(char **paths, int count, char *parent_dir)
{
	struct stat sb_a;
	struct stat sb_b;
	char *path_a;
	char *path_b;
	for (int i = 0; i < count - 1; i++)
	{
        for (int j = 0; j < count - i - 1; j++)
		{
			if (parent_dir[0] != '#')
			{
				path_a = path_join(parent_dir, paths[j]);
				path_b = path_join(parent_dir, paths[j + 1]);
			}
			else
			{
				path_a = paths[j];
				path_b = paths[j + 1];
			}
            if (stat(path_a, &sb_a) == 0 && stat(path_b, &sb_b) == 0)
            {
                if (sb_a.st_mtime < sb_b.st_mtime)
                {
                    swap(&paths[j], &paths[j + 1]);
                }
            }
			if (parent_dir[0] != '#')
			{
				free(path_a);
				free(path_b);
			}
        }
    }
}