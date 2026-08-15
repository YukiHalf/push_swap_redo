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
				rotateStack(stack_a,'a',1);
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
		//printf("%ld < %d\n",tmp->data,candidate);
		if(tmp->data < candidate && tmp->data > max)
			{
			//printf("is good %ld %d\n",tmp->data,candidate);

				target = tmp;
				max = tmp->data;
			}
		tmp = tmp->next;
	}
return target;
}

void meetPair(t_stack *stack_a, t_stack *stack_b,int canInd,int tarInd)
{
	int rCountCand;
	int rCountTarg;

	rCountCand = optimizedRotate(stack_a,canInd);
	rCountTarg = optimizedRotate(stack_b,tarInd);
			printf("%d %d meetPair\n",rCountCand,rCountTarg);
	if(rCountCand >= 0 && rCountTarg >= 0)
	{
		while(rCountCand && rCountTarg)
		{
			rotateBothStacks(stack_a,stack_b,0);
			rCountCand--;
			rCountTarg--;
		}
	}else if(rCountCand < 0 && rCountTarg < 0)
		while(rCountCand < 0 && rCountTarg < 0)
		{
			rotateBothStacks(stack_a,stack_b,1);
			rCountCand++;
			rCountTarg++;
		}
	doRotationStack(stack_a,rCountCand,'a');
	doRotationStack(stack_b,rCountTarg,'b');
	pushStack(stack_b,stack_a,'b');
}

void findPair(t_stack *stack_a,t_stack *stack_b)
{
	t_node *tmp;
	int canInd;
	int minMoves;
	int currMoves;
	t_node *target;

	minMoves = stack_a->size + stack_b->size;
	tmp = stack_a->head;
	while(tmp)
	{
		target = findTarget(stack_b,tmp->data);
		currMoves = calcMoves(stack_a,stack_b,tmp,target);
		if(currMoves < minMoves)
		{
				minMoves = currMoves;
				canInd = tmp->index;
				printf("%d min pari %ld %ld\n",minMoves,tmp->data,target->data);
		}
		tmp = tmp->next;
	}
	printf("%d pari %ld\n",canInd,target->data);
	meetPair(stack_a,stack_b,canInd,target->index);
//printf("yo%ld %ld %d\n",target->data,candidate->data,minMoves);
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


void turkSort(t_stack *stack_a, t_stack *stack_b)
{
	pushStack(stack_b,stack_a,'b');
	pushStack(stack_b,stack_a,'b');
	pushStack(stack_b,stack_a,'b');
	pushStack(stack_b,stack_a,'b');

	DEBUG_printStack(stack_a);
	DEBUG_printStack(stack_b);

	//while(stack_a->size > 3)
	//{
		findPair(stack_a,stack_b);
	//}
	DEBUG_printStack(stack_a);
	DEBUG_printStack(stack_b);
	//simpleSort(stack_a);
	//while(stack_b)
	//{
	//	///
	//}
	//doRotationStack(stack_a,optimizedRotate(stack_a,0),'a');
}
