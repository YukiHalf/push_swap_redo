#ifndef PUSH_SWAP_H
#define PUSH_SWAP_H

#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include "libft/libft.h"

#define MAX_INT 2147483647
#define MIN_INT (-2147483647 - 1)

typedef struct node {
	int nr;
	struct node *next;
} node_t;


// Utils
int has_alpha(char *s);

#endif
