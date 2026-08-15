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
int addNodeStack(t_stack *stack, long number);
int checkDupes(t_node *node);
void sortStacks(t_stack *stack_a,t_stack *stack_b);
void simpleSort(t_stack *stack);
void quickSort(t_stack *stack_a,t_stack *stack_b);
void radixSort(t_stack *stack_a,t_stack *stack_b);
void turkSort(t_stack *stack_a, t_stack *stack_b);
int maxIndex(t_stack *stack);
// Moves
void swapStack(t_stack *stack,char x);
void rRotateStack(t_stack *stack,char x,bool print);
void rotateStack(t_stack *stack,char x,bool print);
void pushStack(t_stack *toStack,t_stack *fromStack,char x);
void rotateBothStacks(t_stack *stack_a,t_stack *stack_b,bool reverse);
void doRotationStack(t_stack *stack,int rotations,char x);



/// TO REMOVE
void DEBUG_printStack(t_stack *stack);
#endif
