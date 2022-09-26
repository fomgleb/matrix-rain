#pragma once

#include <ncurses.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

typedef struct s_vector2 {
    int x;
    int y;
} t_vector2;

typedef struct s_cell {
    char symbol;
    int life;
} t_cell;

