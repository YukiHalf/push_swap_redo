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

void quickSort(t_stack *stack_a,t_stack *stack_b)
{
	t_node *tmp;
	int i =0;
	tmp = stack_a->head;
	while(tmp && i < stack_a->size/2)
	{
		if(tmp->index == i)
		{
			pushStack(stack_b,stack_a,'b');
			i++;
		}
		else
		{
			rotateStack(stack_a,'a');
			tmp = stack_a->head;
		}
	}
	simpleSort(stack_a);
	while(stack_b->head)
		pushStack(stack_a,stack_b,'a');
}
