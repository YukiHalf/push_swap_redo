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
		//printf("%d %d %d %d ?= %d \n",i,j,found,tmp->index,index);
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



int calcMoves(t_stack *stack_cand,t_stack *stack_targ,int candInd,int targInd)
{
	int mv_c;
	int mv_t;
	//printf("c %ld t %ld\n",candidate->data,target->data);
	mv_c = optimizedRotate(stack_cand,candInd);
	mv_t = optimizedRotate(stack_targ,targInd);
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

int findTargetA(t_stack *stack,int candidate)
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

void meetPairA(t_stack *stack_a, t_stack *stack_b,int canInd,int tarInd)
{
	int rCountCand;
	int rCountTarg;

	rCountCand = optimizedRotate(stack_a,canInd);
	rCountTarg = optimizedRotate(stack_b,tarInd);
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

void findPairA(t_stack *stack_a,t_stack *stack_b)
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
		target = findTargetA(stack_b,tmp->index);
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
	meetPairA(stack_a,stack_b,canInd,targInd);
//printf("yo%ld %ld %d\n",target->data,candidate->data,minMoves);
}



void meetPairB(t_stack *stack_can, t_stack *stack_tar,int canInd,int tarInd)
{
	int rCountCand;
	int rCountTarg;

	rCountCand = optimizedRotate(stack_can,canInd);
	rCountTarg = optimizedRotate(stack_tar,tarInd);
	//printf("%d %d meetPair\n",rCountCand,rCountTarg);

	if(rCountCand >= 0 && rCountTarg >= 0)
	{
		while(rCountCand && rCountTarg)
		{
			rotateBothStacks(stack_can,stack_tar,0);
			rCountCand--;
			rCountTarg--;
		}
	}else if(rCountCand < 0 && rCountTarg < 0)
		while(rCountCand < 0 && rCountTarg < 0)
		{
			rotateBothStacks(stack_can,stack_tar,1);
			rCountCand++;
			rCountTarg++;
		}
	//printf("%d %d\n",rCountCand,rCountTarg);
	doRotationStack(stack_can,rCountCand,'a');
	doRotationStack(stack_tar,rCountTarg,'b');
	pushStack(stack_tar,stack_can,'a');
}

int minIndex(t_stack *stack)
{
	t_node *node;
	int min;

	node = stack->head;
	min = stack->head->index;
	while(node->next)
	{
		node = node->next;
		if(node->index < min)
			min = node->index;
	}
return min;
}


int findTargetB(t_stack *stack,int candidate)
{
	t_node *tmp;
	long long int min;

	min = maxIndex(stack) + 1;
	tmp = stack->head;
	while(tmp)
	{
		printf("%d > %d | %d\n",tmp->index,candidate,min);
		if(tmp->index > candidate && tmp->index <= min)
			{
			printf("is good %d %d\n",tmp->index,candidate);
				min = tmp->index;
			}
		tmp = tmp->next;
	}
	if(min == maxIndex(stack) + 1)
		return minIndex(stack);
return min;
}

void findPairB(t_stack *stack_a,t_stack *stack_b)
{
	t_node *tmp;
	int canInd;
	int targInd;
	int minMoves;
	int currMoves;
	int target;

	minMoves = stack_a->size + stack_b->size;
	tmp = stack_b->head;
	while(tmp)
	{
		target = findTargetB(stack_a,tmp->index);
		currMoves = calcMoves(stack_b,stack_a,tmp->index,target);

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
	meetPairB(stack_b,stack_a,canInd,targInd);
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

	while(stack_a->size > 3)
	{
		DEBUG_printStack(stack_a,'a');
		DEBUG_printStack(stack_b,'b');
		findPairA(stack_a,stack_b);
	}
	if(isSorted(stack_a) == 1)
		simpleSort(stack_a);
	printf("we go back\n");
	while(stack_b->size > 0)
	{
		DEBUG_printStack(stack_a,'a');
		DEBUG_printStack(stack_b,'b');
		findPairB(stack_a,stack_b);
	}
		DEBUG_printStack(stack_a,'a');
	doRotationStack(stack_a,optimizedRotate(stack_a,0),'a');
		DEBUG_printStack(stack_a,'a');

}
