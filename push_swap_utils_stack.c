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
	printf("oR: %d %d\n",i,j);
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

int calcMoves(t_stack *stack_a,t_stack *stack_b,t_node *candidate,t_node *target)
{
	int mv_c;
	int mv_t;
	printf("c %ld t %ld\n",candidate->data,target->data);
	mv_c = optimizedRotate(stack_a,candidate->index);
	mv_t = optimizedRotate(stack_b,target->index);
	printf("mv_c %d mv_t %d\n",mv_c,mv_t);
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
}

void findPair(t_stack *stack_a,t_stack *stack_b)
{
	t_node *a;
	t_node *b;
	int minMoves;
	t_node *target;

	minMoves = stack_a->size + stack_b->size;
	a = stack_a->head;
	target = NULL;
	while(a)
	{
		b = stack_b->head;
		while(b)
		{
			if((target == NULL) || (b->data < a->data && b->data > target->data))
				target = b;
			b = b->next;
		}
		if((target->data < a->data ) && calcMoves(stack_a,stack_b,a,target) < minMoves)
		{
				minMoves = calcMoves(stack_a,stack_b,a,target);
				printf("%d min\n",minMoves);
		}
		a = a->next;
	}

printf("yo%ld %d\n",target->data,minMoves);
}


void turkSort(t_stack *stack_a, t_stack *stack_b)
{
	pushStack(stack_b,stack_a,'b');
	pushStack(stack_b,stack_a,'b');

	//while(stack_a->size > 3)
	//{
		findPair(stack_a,stack_b);
	//}
}
