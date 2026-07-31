#ifndef PUSH_SWAP_H
#define PUSH_SWAP_H

#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include "libft/libft.h"

#define MAX_INT 2147483647
#define MIN_INT (-2147483647 - 1)

typedef struct node_s {
	long data;
	struct node_s *next;
} t_node;

typedef struct stack_s {
	int lenght;
	t_node *head;
} t_stack;

// Utils
int has_alpha(char *s);
void push_stack(t_stack *stack, long number);
#endif
