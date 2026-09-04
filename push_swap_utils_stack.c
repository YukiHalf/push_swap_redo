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
	while(tmp)
	{
		if(tmp->index == index)
			found = 1;
		if(found == 1)
			j--;
		else
			i++;
		tmp = tmp->next;
	}
	if(i < -(j))
		return(i);
	else
		return (j);
}

int isSorted(t_stack *stack)
{
	t_node *tmp;


	tmp = stack->head;
	while(tmp)
	{
		if(tmp->next && tmp->index > tmp->next->index)
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
			rRotateStack(stack,'a',1);
			if(isSorted(stack) == 1)
				swapStack(stack,'a');
			return;
		}
		rotateStack(stack,'a',1);
		if(isSorted(stack) == 1)
			swapStack(stack,'a');
		else
			return;
		if(isSorted(stack) == 1)
			rotateStack(stack,'a',1);
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
			doRotationStack(stack_a,optimizedRotate(stack_a,i),'a');
	}
	simpleSort(stack_a);
	while(stack_b->head)
		pushStack(stack_a,stack_b,'a');
}



void doRotationStack(t_stack *stack,int rotations,char x)
{
	int i;

	i = 0;
	if(rotations < 0)
	{
		while(i < ft_abs(rotations))
		{
			rRotateStack(stack,x,1);
			i++;
		}
	}else
	{
		while(i < rotations)
		{
			rotateStack(stack,x,1);
			i++;
		}
	}
}


void 	ksort(t_stack *stack_a,t_stack *stack_b)
{
	int i;
	int middle;

	middle = ft_sqrt(stack_a->size) * 1.4;
	i = 0;
	while(stack_a->head)
	{
		if(stack_a->head->index <= i)
		{
			pushStack(stack_b,stack_a,'b');
			i++;
			if(stack_a->head &&	stack_a->head->index > i + middle)
				rotateBothStacks(stack_a,stack_b,false);
			else
				rotateStack(stack_b,'b',true);
		}
		else if(stack_a->head->index <= i + middle)
		{
			pushStack(stack_b,stack_a,'b');
			i++;
		}
	else
		rotateStack(stack_a,'a',true);
	}
}
