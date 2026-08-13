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


void radixSort(t_stack *stack_a,t_stack *stack_b)
{
		int lower;
		int upper;
		int chunk_size;
		int pushed;
		int maxInd;
		int expected;
		int totalSize;
		lower = 0;
		maxInd = maxIndex(stack_a);
		upper = 0;
		chunk_size = maxInd / 3;
		totalSize = stack_a->size;
		while(lower < totalSize)
		{
			upper = lower + chunk_size;
			if(upper > totalSize)
				upper = totalSize;
			expected = upper - lower;
			pushed = 0;
			while(pushed < expected)
			{
			if(stack_a->head->index >= lower && stack_a->head->index < upper)
				{
					pushStack(stack_b,stack_a,'b');
					pushed++;
				}
			else
				rotateStack(stack_a,'a');
			}
			lower = upper;
		}

		while(stack_b->size > 0)
		{
			maxInd = maxIndex(stack_b);
			if(optimizedRotate(stack_b,maxInd))
				while(stack_b->head->index != maxInd)
					rotateStack(stack_b,'b');
			else
				while(stack_b->head->index != maxInd)
					rRotateStack(stack_b,'b');
				pushStack(stack_a,stack_b,'a');
		}
}
