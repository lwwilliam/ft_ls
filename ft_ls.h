#ifndef FT_LS_H
# define FT_LS_H

#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/stat.h>
#include "libft/libft.h"

void cannot_access(char *cmd, char *path);

#endif