#include "ft_ls.h"

void red () {
  write(1, "\033[1;31m", 7);
}

void yellow() {
  write(1, "\033[1;33m", 7);
}

void blue() {
  write(1, "\033[0;34m", 7);
}

void green() {
  write(1, "\033[0;32m", 7);
}

void cyan() {
  write(1, "\033[0;36m", 7);
}

void reset () {
  write(1, "\033[0m", 4);
}