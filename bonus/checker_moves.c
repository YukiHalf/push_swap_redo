#include "checker.h"


void pushStack(t_stack *toStack,t_stack *fromStack,char x,bool print)
{
	t_node *tmp;
	if(!fromStack->head)
		return;
	tmp = fromStack->head;
	fromStack->head = fromStack->head->next;
	tmp->next = toStack->head;
	toStack->head = tmp;
	fromStack->size--;
	toStack->size++;
	if(print)
	{
	write(1,"p",2);
	write(1,&x,1);
	write(1,"\n",1);
	}
}


void rotateStack(t_stack *stack,char x,bool print)
{

	t_node *tmp;

	tmp = stack->head;
	while(tmp->next)
			tmp = tmp->next;
	tmp->next = stack->head;
	tmp = stack->head;
	stack->head = stack->head->next;
	tmp->next = NULL;
	if(print)
	{
	write(1,"r",2);
	write(1,&x,1);
	write(1,"\n",1);
	}
}

void rRotateStack(t_stack *stack,char x,bool print)
{
	t_node *tmp;

	tmp = stack->head;
	while(tmp->next->next)
		tmp = tmp->next;
	tmp->next->next = stack->head;
	stack->head = tmp->next;
	tmp->next = NULL;
	if(print)
	{
	write(1,"rr",2);
	write(1,&x,1);
	write(1,"\n",1);
	}
}


void swapStack(t_stack *stack,char x,bool print)
{
	t_node *tmp;

	if(stack->size == 1)
		return;
	tmp = stack->head->next;
	stack->head->next = tmp->next;
	tmp->next = stack->head;
	stack->head = tmp;
	if(print)
	{
		write(1,"s",1);
		write(1,&x,1);
		write(1,"\n",1);
	}
}


void rotateBothStacks(t_stack *stack_a,t_stack *stack_b,bool reverse,int print)
{
	if(reverse)
	{
		rRotateStack(stack_a,'a',0);
		rRotateStack(stack_b,'b',0);
		if(print)
		write(1,"r",1);
	}else
	{
		rotateStack(stack_a,'a',0);
		rotateStack(stack_b,'b',0);
	}
	if(print)
	{
	write(1,"rr",2);
	write(1,"\n",1);
	}
}
