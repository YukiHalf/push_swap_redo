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
	int bit;
	int max_index;
	int count;
	bit = 0;
	max_index = stack_a->size - 1;
	while((max_index >> bit) != 0 || isSorted(stack_a) == 1)
	{
		int i = 0;
		count = stack_a->size;
		while(i < count)
		{
		if(((stack_a->head->index >> bit) & 1) == 0)
			pushStack(stack_b,stack_a,'b');
		else
			rotateStack(stack_a,'a');
		i++;
		}
		while(stack_b->size > 0)
		{
			if(optimizedRotate(stack_b,maxIndex(stack_b)))
				while(stack_b->head->index != maxIndex(stack_b))
					rotateStack(stack_b,'b');
			else
				while(stack_b->head->index != maxIndex(stack_b))
					rRotateStack(stack_b,'b');
				pushStack(stack_a,stack_b,'a');
		}
		bit++;
	}
}
