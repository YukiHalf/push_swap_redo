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
	int index;
	struct node_s *next;
} t_node;

typedef struct stack_s {
	int size;
	t_node *head;
} t_stack;

// Utils
int hasAlpha(char *s);
int isSorted(t_stack *stack);
int pushStack(t_stack *stack, long number);
int checkDupes(t_node *node);
void sortStacks(t_stack *stack_a,t_stack *stack_b,int size);
void simpleSort(t_stack *stack);
// Moves
void swapStack(t_stack *stack,char x);
void rRotateStack(t_stack *stack,char x);
void rotateStack(t_stack *stack,char x);
#endif
