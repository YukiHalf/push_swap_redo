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

int calcMoves(t_stack *stack_a,t_stack *stack_b,int candInd,int targInd)
{
	int mv_c;
	int mv_t;
	//printf("c %ld t %ld\n",candidate->data,target->data);
	mv_c = optimizedRotate(stack_a,candInd);
	mv_t = optimizedRotate(stack_b,targInd);
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

int findTarget(t_stack *stack,int candidate)
{
	t_node *tmp;
	int max;

	max = -1;
	tmp = stack->head;
	while(tmp)
	{
		//printf("%ld < %d\n",tmp->data,candidate);
		if(tmp->index < candidate && tmp->index > max)
			{
			//printf("is good %ld %d\n",tmp->data,candidate);
				max = tmp->index;
			}
		tmp = tmp->next;
	}
	if(max == -1)
		return maxIndex(stack);
return max;
}

void meetPair(t_stack *stack_a, t_stack *stack_b,int canInd,int tarInd)
{
	int rCountCand;
	int rCountTarg;

	rCountCand = optimizedRotate(stack_a,canInd);
	rCountTarg = optimizedRotate(stack_b,tarInd);
			printf("%d %d meetPair %d %d\n",rCountCand,rCountTarg,canInd,tarInd);
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
	int targInd;
	int minMoves;
	int currMoves;
	int target;

	minMoves = stack_a->size + stack_b->size;
	tmp = stack_a->head;
	while(tmp)
	{
		target = findTarget(stack_b,tmp->index);
		currMoves = calcMoves(stack_a,stack_b,tmp->index,target);

		if(currMoves < minMoves)
		{

				minMoves = currMoves;
				canInd = tmp->index;
				targInd = target;
		printf("can=%d targ=%d  currMoves=%d minMoves=%d condition=%d\n",
      canInd,target, currMoves, minMoves, currMoves < minMoves);
		}
		tmp = tmp->next;
	}
	printf("%d pari %d\n",canInd,targInd);
	meetPair(stack_a,stack_b,canInd,targInd);
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


	DEBUG_printStack(stack_a);
	DEBUG_printStack(stack_b);

	while(stack_a->size > 3)
	{
		findPair(stack_a,stack_b);
	}
	DEBUG_printStack(stack_a);
	DEBUG_printStack(stack_b);
	simpleSort(stack_a);
	//while(stack_b)
	//{
	//	///
	//}
	//doRotationStack(stack_a,optimizedRotate(stack_a,0),'a');
}
