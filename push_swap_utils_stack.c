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
		if(found)
			j--;
		else
			i++;
		tmp = tmp->next;
	}
	//printf("%d oR: %d %d\n",index,i,j);
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
			doRotationStack(stack_a,optimizedRotate(stack_a,i),'a');
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
			doRotationStack(stack_b,optimizedRotate(stack_b,maxInd),'b');
			pushStack(stack_a,stack_b,'a');
		}
}

int calcMoves(t_stack *stack_a,t_stack *stack_b,t_node *candidate,t_node *target)
{
	int mv_c;
	int mv_t;
	//printf("c %ld t %ld\n",candidate->data,target->data);
	mv_c = optimizedRotate(stack_a,candidate->index);
	mv_t = optimizedRotate(stack_b,target->index);
	//printf("mv_c %d mv_t %d\n",mv_c,mv_t);
	if((mv_c <= mv_t ) && (mv_c >= 0 && mv_t >= 0) )
		return(mv_t);
	else if((mv_c >= mv_t ) && (mv_c >= 0 && mv_t >= 0) )
		return (mv_c);
	else if((mv_c <= mv_t ) && (mv_c < 0 && mv_t < 0) )
		return(ft_abs(mv_t));
	else if((mv_c >= mv_t ) && (mv_c < 0 && mv_t < 0) )
		return(ft_abs(mv_c));
	else if((mv_c < 0 && mv_t >= 0) ||  (mv_t < 0 && mv_c >= 0))
		return(ft_abs(mv_c) + ft_abs(mv_t));
	else
		return (0);
}

t_node  *findTarget(t_stack *stack,int candidate)
{
	t_node *tmp;
	t_node *target;
	int max;

	max = MIN_INT;
	target = stack->head;
	tmp = stack->head;
	while(tmp)
	{
		printf("%ld < %d\n",tmp->data,candidate);
		if(tmp->data < candidate && tmp->data > max)
			{
			printf("is good %ld %d\n",tmp->data,candidate);

				target = tmp;
				max = tmp->data;
			}
		tmp = tmp->next;
	}
return target;
}

void findPair(t_stack *stack_a,t_stack *stack_b)
{
	t_node *a;
	t_node *b;
	int minMoves;
	int currMoves;
	t_node *target;

	minMoves = stack_a->size + stack_b->size;
	a = stack_a->head;
	while(a)
	{
		target = findTarget(stack_b,a->data);
		currMoves = calcMoves(stack_a,stack_b,a,target);
		if(currMoves < minMoves)
		{
				minMoves = currMoves;
				printf("%d min pari %ld %ld\n",minMoves,a->data,target->data);
		}
		a = a->next;
	}

printf("yo%ld %d\n",target->data,minMoves);
}

void doRotationStack(t_stack *stack,int rotations,char x)
{
	int i;

	i = 0;
	if(rotations < 0)
	{
		while(i < ft_abs(rotations))
		{
			rRotateStack(stack,x);
			i++;
		}
	}else
	{
		while(i < rotations)
		{
			rotateStack(stack,x);
			i++;
		}
	}
}


void turkSort(t_stack *stack_a, t_stack *stack_b)
{
	pushStack(stack_b,stack_a,'b');
	pushStack(stack_b,stack_a,'b');

	//while(stack_a->size > 3)
	//{
		findPair(stack_a,stack_b);
	//}
	//simpleSort(stack_a);
	//while(stack_b)
	//{
	//	///
	//}
	//doRotationStack(stack_a,optimizedRotate(stack_a,0),'a');
}
