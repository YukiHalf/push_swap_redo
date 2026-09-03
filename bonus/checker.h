#ifndef CHECKER_H
#define CHECKER_H

#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include "../libft/libft.h"

typedef enum moves_s{
	SWAP,
	PUSH,
	ROTATE,
	RROTATE,
} moves_t;


typedef struct node_s {
	long data;
	int index;
	struct node_s *next;
} t_node;

typedef struct stack_s {
	int size;
	t_node *head;
} t_stack;

void pushStack(t_stack *toStack,t_stack *fromStack,char x,bool print);
void rotateStack(t_stack *stack,char x,bool print);
void rRotateStack(t_stack *stack,char x,bool print);
void swapStack(t_stack *stack,char x,bool print);
void rotateBothStacks(t_stack *stack_a,t_stack *stack_b,bool reverse,int print);


int isSorted(t_stack *stack);
#endif




