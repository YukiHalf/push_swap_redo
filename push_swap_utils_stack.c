#include "push_swap.h"


int optimizedRotate(t_stack *stack,int index)
{
	int i;
	int j;
	int found;
	t_node *tmp;

	i = 0;
	j = 0;
	found = 0;
	tmp = stack->head;
	while(tmp->next)
	{
		if(tmp->index == index)
			found = 1;
		if(found)
			j++;
		else
			i++;
		tmp = tmp->next;
	}
	printf("%d %d = %d\n",i,j,i < j);
	return(i < j);
}

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
	int i;

	i = 0;
	while(stack_a->size != 3)
	{
		if(stack_a->head->index == i)
		{
			pushStack(stack_b,stack_a,'b');
			i++;
		}
		else
		{
			if(optimizedRotate(stack_a,i))
				while(stack_a->head->index != i)
					rotateStack(stack_a,'a');
			else
				while(stack_a->head->index != i)
					rRotateStack(stack_a,'a');
		}
	}
	simpleSort(stack_a);
	while(stack_b->head)
		pushStack(stack_a,stack_b,'a');
}
