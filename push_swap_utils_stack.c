#include "push_swap.h"

int isSorted(t_stack *stack)
{
	t_node *tmp;

	tmp = stack->head;
	while(tmp)
	{
		if(tmp->next && tmp->data > tmp->next->data)
			return 1;
		tmp = tmp->next;
	}
	return 0;
}

void rotateStack(t_stack *stack,char x)
{

	t_node *tmp;

	tmp = stack->head;
	while(tmp->next)
			tmp = tmp->next;
	tmp->next = stack->head;
	tmp = stack->head;
	stack->head = stack->head->next;
	tmp->next = NULL;
	write(1,"r",2);
	write(1,&x,1);
	write(1,"\n",1);
}

void rRotateStack(t_stack *stack,char x)
{
	t_node *tmp;

	tmp = stack->head;
	while(tmp->next->next)
		tmp = tmp->next;
	tmp->next->next = stack->head;
	stack->head = tmp->next;
	tmp->next = NULL;
	write(1,"rr",2);
	write(1,&x,1);
	write(1,"\n",1);
}


void swapStack(t_stack *stack,char x)
{
	t_node *tmp;

	if(stack->size == 1)
		return;
	tmp = stack->head->next;
	stack->head->next = tmp->next;
	tmp->next = stack->head;
	stack->head = tmp;
	write(1,"s",1);
	write(1,&x,1);
	write(1,"\n",1);
}

void simpleSort(t_stack *stack)
{
	t_node *node;

	node = stack->head;

	if(node->index < node->next->index)
		{
			rRotateStack(stack,'a');
			if(isSorted(stack) == 1)
				swapStack(stack,'a');
			return;
		}
		rotateStack(stack,'a');
		if(isSorted(stack) == 1)
			swapStack(stack,'a');
		else
			return;
		if(isSorted(stack) == 1)
			rotateStack(stack,'a');
}

